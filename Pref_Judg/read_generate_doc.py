#!/usr/bin/env python
import csv
from os import listdir
from os.path import isfile, join
import re

file_path = "./files/all_401-450/"


onlyfiles = [f for f in listdir(file_path) if isfile(join(file_path, f))]

def check_if_doc(qrel_file):
   doc_list = set(get_qrel(qrel_file, 2)) #get doc list in judgement
   for f in onlyfiles:
      if f in doc_list:
         doc_list -= set([f])
   print doc_list


def get_qrel(qrel_file, index): #index 0-topic 2-doc_id 3-relevance
	a_list = []
	with open(qrel_file, "r") as f:
   		for line in f:
			a_list.append(line.split(' ')[index])	

	f.close()
	return a_list		

#write array_content into file_name
def write_csv(file_name, array_content):
	with open(file_name, 'wb') as myfile:
		for row in array_content:
			myfile.write(row)
	myfile.close()

#read data in collection and extract the document
def read_and_extract (collection_file, qrel_file):
	
	#do filtering by qrel. get the doc_id in the qrel file
	doc_list = get_qrel(qrel_file, 2)

	#
	file_name = ""
	array_content = []

	#flags
	text_begin = 0
	proc_file = 0

	#counter
	doc_count = 0

	with open(collection_file, "r") as f:
   		for line in f:
   			if "<DOC>" in line: #a begin of a document
   				#a new document
   				doc_count += 1
   				proc_file = 0
   				continue
   			elif "<DOCNO>" in line: #get the document id
   				#set document id
   				file_name = re.search('<DOCNO> (.+?) </DOCNO>', str(line)).group(1)#line.split(' ')[1]
   				if file_name in doc_list:
   					print ">> processing file: "+file_name
   					proc_file = 1
   			
   			if proc_file:
   				if (("<TEXT>" in line) | ("<GRAPHIC>" in line)): #get the content of the document
   					text_begin = 1
   				elif (("</TEXT>" in line) | ("</GRAPHIC>" in line)):
   					text_begin = 0
   					write_csv(file_path+file_name, array_content) #write content into file
   					array_content = [] #reset the content
   				else:
   					if text_begin:
   						#store the text in array
   						array_content.append(line) 

   	print "totally " + str(doc_count) +" documents"



