from random import randint
import random
import csv
from bs4 import BeautifulSoup

csv_file = "402-fix.csv"
file_path = "./files/all_401-450/"
longest_group_len = 6

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
		upper_limit = len(doc_list)/alpha

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

# Create unit for each group of each topic.
# Each document will be randomly paired with
#   _at least_ beta (expected 2*beta) documents 
#   in the same group 
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

# Create unit for each group of each topic.
# Each document will be randomly paired with
#   _exact_ beta documents in the same group 
def uniting_2(beta, a_dict):
	#write csv file head
	title = ["topic"]
	for i in range(1, beta*longest_group_len+1):
		title.append("doc"+str(i))

	write_csv(csv_file, title)
	
	#generate pair list
	for topic in a_dict:
		i=0
		print "===topic "+str(topic)+"==="
		for group in a_dict[topic]:
			doc_counter={}
			i+=1;

			list_len = beta*len(group)/2 # get the expected list length
			pair_list=[] # reset pair list
			#while(list_len!=len(pair_list)): # the evidence to find the right solution
											 # otherwise, try again
			pair_list=[]
			for doc in group:
				doc_counter[doc] = beta
			# find the pair list
			pair_list=find_pair_list(doc_counter, group[0:], random.choice(group),[],1)
			
			print len(pair_list)
			if(list_len!=len(pair_list)):
				print "ERROR!"
			else:#print pair_list
				print "------group "+str(i)+"------"
				for pair in pair_list:
				 	print pair

			# generate row for a unit and write to csv file
			# generate_row(csv_file, topic, pair_list)



def find_pair_list(doc_counter, group, ele1, pairs, level):
	flag=1
	removed_eles=[]
	if(ele1 ==(-1)):
		print ">> ele1 is -1.  level: "+str(level)
		return pairs
	elif(len(group)==1): #this ele1 is the only left, cannot pair
		print ">> ele1 is the only left.  level: "+str(level)
		return pairs


	while(1): # keep pairing until return

		# pick a document for pairing
		ele2 = pick_doc(ele1, doc_counter, group, pairs)
		flag +=1
		
		
		if(ele2!=(-1)): # if sucessfully pair with a doc
			pairs.append(set([ele1,ele2]))
			doc_counter[ele1] -= 1
			doc_counter[ele2] -= 1
			
			#last pair
			if((doc_counter[ele1]==0)&(doc_counter[ele2]==0)):

				group.remove(ele1)
				group.remove(ele2)

				#	This should be the last pair, but if there is something left,
				#	means, this is not the solution.
				if(len(dict((key,value) for key, value in doc_counter.iteritems() if value >0))):
					# Roll back
					# Remove from the pair list
					pairs.remove(set([ele1,ele2]))
					doc_counter[ele1] += 1
					doc_counter[ele2] += 1
					group.append(ele1)
					group.append(ele2)
					
					# the pair list will NOT contain the new pair
					return pairs
				else:			
					# last pair
					# task completed!!!
					return pairs
						

			#Not the last pair, so pick one doc to stay
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
				group+=removed_eles
				return new_pairs
			else:
				# Not this branch, but how about this?
				new_pairs = find_pair_list(doc_counter, group, replaced, pairs,level+1)
				if (len(new_pairs)>pairs_len):
					# Successfully found
					group+=removed_eles
					return new_pairs
				else:
					# This pair cannot be formed because of no further solution
					# So roll back
					if((ele1 in removed_eles) & (doc_counter[ele1]==0)):
						removed_eles.remove(ele1)
						group.append(ele1)
					
					if((ele2 in removed_eles) & (doc_counter[ele2]==0)):
						removed_eles.remove(ele2)
						group.append(ele2)

					doc_counter[ele1] += 1
					doc_counter[ele2] += 1

					# Remove from the pair list
					pairs.remove(set([ele1,ele2]))

					# ele2 is removed for non-consideration
					removed_eles.append(ele2)
					group.remove(ele2)
					
					# if ele1 is only one left in the group
					# just return the pair list without new pair added
					if((len(group)==1) & (ele1 in group)): 
						group+=removed_eles
						return pairs
					
		else:
			# Totally hopeless. Go back to previous level to cancel
			group+=removed_eles # put the removed elements back
			
			# no new pair is added.
			return pairs # the pair list will NOT contain the new pair
			
	
	# print "=======not this plan. Level: "+str(level)
	# return pairs
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

					if(len(dict((key,value) for key, value in doc_counter.iteritems() if value >1))):
						#print "should return NULL"
						# print str(ele1)+","+str(ele2)
						# print doc_counter
						group+=removed_eles
						return -1

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

# Write rows into file_name, _appendly_
# pairs: [d1,d2],[d2,d3],[d3,d4],...
# row:
# topic_id, d1_id, d2_id, d3_id, ... 
def generate_row(csv_file, topic, pairs):
	row = [topic]
	previous_pair = []
	i=0
	for pair in pairs:
		i += 1
		row.append(pair[0])
		row.append(pair[1])
	# 	if (i > 1):
	# 		if doc1 in previous_pair:
	# 			#doc1 was the doc that was kept
	# 			#insert previous pair
	# 			previous_pair.remove(doc1)
	# 		else:
	# 			#doc2 was the doc that was kept
	# 			#insert previous pair
	# 			previous_pair.remove(doc2)
			
	# 		row.append(previous_pair[0])
	# 		#row.append(get_doc_content(previous_pair[0])) 

	# 	previous_pair = [doc1, doc2]

	# # last pair
	# if doc1 in previous_pair:
	# 	#doc1 was the doc that was kept
	# 	row.append(doc1)
	# 	#row.append(get_doc_content(doc1))
	# 	row.append(doc2)
	# 	#row.append(get_doc_content(doc2))
		
	# else:
	# 	#doc2 was the doc that was kept
	# 	row.append(doc2)
	# 	#row.append(get_doc_content(doc2))
	# 	row.append(doc1)
	# 	#row.append(get_doc_content(doc1))

	# write to file
	#print row
	write_csv(csv_file, row)

def get_doc_content(doc_id):
	with open(file_path+doc_id, 'r') as myfile:
		data = myfile.read().replace('\n', '<\br>')
	return str(data[0:3000])

def write_csv(csv_file, array_content):
	with open(csv_file, 'a') as mycsvfile:
		datawriter = csv.writer(mycsvfile)
		datawriter.writerow(array_content)
	mycsvfile.close()