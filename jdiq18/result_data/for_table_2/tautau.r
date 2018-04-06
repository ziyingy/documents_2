d <- data.frame()

tmp <- read.csv("trec2004-rel_p.csv", skip=1, header=F)
names(tmp) <- c("topic","rel","str","phi")
tmp$scheme <- "tau-ap"
d <- rbind(d, tmp)

tmp <- read.csv("trec2004-rel_p_NDCG.csv", skip=1, header=F)
names(tmp) <- c("topic","rel","str","phi")
tmp$scheme <- "tau-ndcg"
d <- rbind(d, tmp)

tmp <- read.csv("trec2004-rel_p_NDCG_RBO.csv", skip=1, header=F)
names(tmp) <- c("topic","rel","str","phi")
tmp$scheme <- "rbo-ndcg"
d <- rbind(d, tmp)

tmp <- read.csv("trec2004-rel_p_RBO.csv", skip=1, header=F)
names(tmp) <- c("topic","rel","str","phi")
tmp$scheme <- "rbo-ap"
d <- rbind(d, tmp)


# count of cases <0.8, < 0.9, >= 0.9
for (x in (unique(d$scheme))) {
    tmp <- d[d$scheme == x,]

    tautau <- cor.test(tmp$phi, tmp$rel, method="k")
    meanphi <- mean(tmp$phi)
    counts <- table(cut(tmp$str, c(0,0.8, 0.9,1)))

    cat(print(x),"\n")
    cat(print(paste("\t\t&&",counts[1],
                "\n\t\t\t&",counts[2],
                "\n\t\t\t\t&",counts[3],
                "\n\t\t\t\t\t&&",tautau$estimate,
                "\n\t\t\t\t\t\t&",tautau$p.value,
                "\n\t\t\t\t\t\t\t&",meanphi,
                "\n",
        sep="")))
}

# kendall's tau and p-value

# average phi


tapply(d$, d$scheme, function(x){mean(x$rel)})
