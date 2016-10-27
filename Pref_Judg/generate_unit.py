from random import randint
import random


def get_topic_doc_dict(qrel_file): #dict {topic_i:[doc1,doc2,...], topic_j:[...], ...} 
								   #will be returned
	a_dict = {}
	with open(qrel_file, "r") as f:
   		for line in f:
			elem = line.split(' ') #elem[0]-topic; elem[2]-document; elem[3]-relevance
			if a_dict.has_key(elem[0]):
				a_dict[elem[0]].append(elem[2])
			else:
				a_dict[elem[0]] = [elem[2]]


	f.close()
	return a_dict

def grouping(alpha, a_dict): #dict {topic_i:[[doc1,doc2,...],[...],..], topic_j:[...], ...} 
							 #will be returned
	
	for topic in a_dict:
		#get the doc list for each topic
		doc_list = a_dict[topic]

		#re-initialize the list
		a_dict[topic] = []
		for i in range(0, alpha):
			a_dict[topic].append([])

		#set the upper limit of each group
		upper_limit = len(doc_list)/alpha+1

		#spread documents in to different groups
		for doc in doc_list:
			inserted = 0
			while(not inserted):
				gorup_no = randint(1,alpha)
				if (len(a_dict[topic][gorup_no-1]) < upper_limit):
					a_dict[topic][gorup_no-1].append(doc)
					inserted = 1

	#printing
	for topic in a_dict:
		print topic
		for group in a_dict[topic]:
			print "\t"+str(len(group))

	return a_dict


def uniting(beta, a_dict):
	counter = 0
	pairs_for_topic = []

	for topic in a_dict:
		pairs_for_topic = []
		for group in a_dict[topic]:
			group_pairs = []
			for doc in group:
				pairs = []
				while (len(pairs)<beta):
					ele = random.choice(group)
					if(ele is not doc):
						if(set([ele,doc]) in group_pairs):
							#print "! pair"+ str([ele,doc]) +"exist in group pairs"
							continue
						elif(set([ele,doc]) in pairs):
							#print "! pair"+ str([ele,doc]) +"exist in pairs"
							continue
						else:
							pairs.append(set([ele,doc]))
					else:
						continue
				group_pairs = group_pairs+pairs
			print "------------------------------------"
			#print pairs number of each document
			for doc in group:
				counter = 0			
				for pair in group_pairs:
					if doc in pair:
						counter +=1
				print "\t"+str(doc)+"  "+str(counter)
			
			for pair in group_pairs:
				print pair
			
			pairs_for_topic += group_pairs

		print "There are totally "+str(len(pairs_for_topic))+" pairs generated."


def uniting_2(beta, a_dict):
	for topic in a_dict:
		for group in a_dict[topic]:
			doc_counter={}

			list_len = beta*len(group)/2
			pair_list=[]
			while(list_len!=len(pair_list)): # the evidence to find the right solution
											 # otherwise, try again
				pair_list=[]
				for doc in group:
					doc_counter[doc] = beta
				pair_list=find_pair_list(doc_counter, group[0:], random.choice(group),[],1)
				#print pair_list
				print len(pair_list)
			print "------topic "+str(topic)+"------"
			for pair in pair_list:
				print pair


def find_pair_list(doc_counter, group, ele1, pairs, level):
	flag=1
	removed_eles=[]
	if(ele1 ==(-1)):
		return pairs
	elif(doc_counter[ele1]==0):
		return pairs
	elif(len(group)==1): #this ele1 is the only left, cannot pair
		return pairs


	while(flag<10): #at most try 10 times to avoid no solution
		# print "ele1: "+str(ele1)+"\tlevel: "+str(level)
		# print group
		# print "pairs:"+str(pairs)

		# pick a document for pairing
		ele2 = pick_doc(ele1, doc_counter, group, pairs)
		flag +=1
		#
		if(ele2!=(-1)):
			#print "ele2 ["+str(ele2)+"] is picked. flag:"+str(flag)
			pairs.append(set([ele1,ele2]))
			doc_counter[ele1] -= 1
			doc_counter[ele2] -= 1
			
			#last pair
			if((doc_counter[ele1]==0)&(doc_counter[ele2]==0)):
				# print "pairs returned. \tlevel: "+str(level)
				# print pairs
				group+=removed_eles
				return pairs

							

			#pick one to stay
			replaced = -1
			if(doc_counter[ele1]==0):
				#ele1 is removed from group
				group.remove(ele1)
				removed_eles.append(ele1)
				#keep the ele2
				kept = ele2			
			
			elif(doc_counter[ele2]==0):
				#ele1 kept
				group.remove(ele2)
				removed_eles.append(ele2)
				#keep the ele1
				kept = ele1
			else:
				# randomly pick one to stay, ele1 is the picked one		
				if(randint(0,1)):
					kept = ele2
					replaced = ele1
				else:
					kept = ele1
					replaced = ele2

			pairs_len = len(pairs)

			#recursion to fine further pairs
			new_pairs = find_pair_list(doc_counter, group, kept, pairs,level+1)
			if (len(new_pairs)>pairs_len):
				# Successfully found
				# print ">>> pairs:"+str(pairs_len)
				# print ">>> new list:"+str(new_pairs)
				# print ">>> level: "+str(level)
				group+=removed_eles
				return new_pairs
			else:
				# Not this branch, but how about this?
				new_pairs = find_pair_list(doc_counter, group, replaced, pairs,level+1)
				if (len(new_pairs)>pairs_len):
					# Successfully found
					# print "new list:"+str(new_pairs)
					# print "level: "+str(level)
					group+=removed_eles
					return new_pairs
				else:
					# This pair cannot be formed because of no further solution
					# ele2 is removed for non-consideration"
					if(replaced!=(-1)):
						removed_eles.append(ele2)
						group.remove(ele2)

					# Roll back
					doc_counter[ele1] += 1
					doc_counter[ele2] += 1

					if((ele1 in removed_eles) & (doc_counter[ele1]>0)):
						removed_eles.remove(ele1)
						group.append(ele1)

					# Remove from the pair list
					pairs.remove(set([ele1,ele2]))

					#no solution for this chosen.
					
		else:
			# Totally hopeless. Go back to previous level to cancel
			# print "not this plan, go back"
			group+=removed_eles
			return pairs # the length of pairs will stay the same as passed. 
			# no new pair is added.

	return pairs
	# 1. successfully find solution and return
	# 2. tried too many time, flag > 10

def pick_doc(ele1, doc_counter, group, pairs):
	group.remove(ele1)
	removed_eles=[ele1]

	while(1):
		# If group is empty, return -1
		if not group:
			# print "cannot find element for ["+str(ele1)
			group+=removed_eles
			return -1	
		
		# Pick a document from group
		ele2 = random.choice(group)
		if(ele2 is not ele1):
			if ((doc_counter[ele1]==1) & (doc_counter[ele2]==1)):
				if (set([ele1,ele2]) in pairs): #only choice, but it exist
					# print "not this plan."
					group+=removed_eles
					return -1
				
				if(len(group)==1): #just these two remain
					#print "found element ["+str(ele2)+"] for ["+str(ele1)
					group+=removed_eles
					return ele2;
				else:
					removed_eles.append(ele2)
					group.remove(ele2)
					continue
			# exist in pairs
			elif(set([ele1,ele2]) in pairs):
				#print "! pair"+ str([ele,doc]) +"exist in pairs"
				removed_eles.append(ele2)
				group.remove(ele2)
				continue
			# found one and return
			else:
				# print "found element ["+str(ele2)+"] for ["+str(ele1)
				group+=removed_eles
				return ele2;

#uniting_2(4, {'000':[[1,2,3,4,5,6,7]]})