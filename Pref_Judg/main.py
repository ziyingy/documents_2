import read_generate_doc
import generate_unit

qrel_file = "data/sormunen_qrels/sormunen_qrels_copy"
collection_files = "data/collections/latimes"

alpha = 11 #group number
beta = 4  #pairs for each document in the group
		  #make sure it is even

#--read collection and extract document (only those in the pool) into
#--seperate files, file directory is defined in read_generate_doc.py
#read_generate_doc.read_and_extract(collection_files, qrel_file)

#--check if all documents in judgments have been extracted
#read_generate_doc.check_if_doc(qrel_file)

topic_doc_dict = generate_unit.get_topic_doc_dict(qrel_file)

#for t in topic_doc_dict:
#	print str(t)+"\t"+str(len(topic_doc_dict[t]))

#for each sampling
topic_doc_dict = generate_unit.grouping(alpha, topic_doc_dict)

#generate_unit.uniting(beta, topic_doc_dict)

generate_unit.uniting_2(beta, topic_doc_dict)

