q.123 <- read.table("sormunen_qrels_orig/qrels_123")
q.23 <- read.table("sormunen_qrels_orig/qrels_23")
q.3 <- read.table("sormunen_qrels_orig/qrels_3")
q.0 <- read.table("conv/nonrel.conv")

# due to overlap of documents for different topics, create a combined
# topic.document field
q.123[,5] <- paste(q.123[,1], q.123[,3], sep=".")
q.23[,5] <- paste(q.23[,1], q.23[,3], sep=".")
q.3[,5] <- paste(q.3[,1], q.3[,3], sep=".")
q.0[,5] <- paste(q.0[,1], q.0[,3], sep=".")

# merge the set of all rels and all non-rels
q.all <- rbind(q.0, q.123)

# use the nested files to assign level 2 and 3 rels
q.all$V4[q.all$V5 %in% q.23$V5] <- 2
q.all$V4[q.all$V5 %in% q.3$V5] <- 3

# re-sort file
q.all <- q.all[order(q.all$V5),] 

# confirm number of docs
table(q.all$V4)

# write table
write.table(q.all[,1:4], "sormunen_qrels", quote=F, row.names=F, col.names=F)
