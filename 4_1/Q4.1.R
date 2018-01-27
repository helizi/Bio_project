global <- read.csv(file = "~/CLionProjects/untitled/global.csv", check.names = FALSE)
mat<-matrix(list(), nrow=3, ncol=2)
for (i in 1:5){
  for(j in i+1:5){
    mat[[i,j]] <- (-1/(1.9 * 10^)-3)*ln(1 - 4/3 * global[[i,j]]/18810)
  }
}