CSV3_4 <- read.csv(file = "~/CLionProjects/untitled/3-4.csv", check.names = FALSE)

##3-4
tree3_4 = upgma(CSV3_4)
png(filename="~/CLionProjects/untitled/UPGMA_3-4.png")
plot(tree3_4)
dev.off()
nei_3_4 = nj(as.dist(CSV3_4))
png(filename="~/CLionProjects/untitled/NJ_3-4.png")
plot(nei_3_4)
dev.off()