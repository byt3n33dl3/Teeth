#!/usr/bin/env Rscript
## summarize hits
output = commandArgs(T)[2] ## output table
filepath = commandArgs(T)[1]  ## input dante gff3
if (length(commandArgs(T))==2){
  summarized_by = NA
}else{
  summarized_by = strsplit(commandArgs(T)[-(1:2)], split = ",")[[1]]
}

readGFF3fromDante = function(filepath){
  dfraw=read.table(filepath, as.is = TRUE)
  gff_df = dfraw[,1:8]
  colnames(gff_df) = c("seqid", "source", "type", "start", "end", "score",
                    "strand", "phase")
  ## assume same order, same attributes names
  ## TODO make ti more robust - order can change!
  gffattr_list = lapply(
    strsplit(dfraw[,9],split=c("=|;")),
    function(x)x[c(FALSE,TRUE)]
  )
  ## some rows are not complete - in case of ambiguous domains
  L = sapply(gffattr_list, length)
  short = L  < max(L)
  if (any(short)){
    gffattr_list[short] = lapply(gffattr_list[short],function(x) c(x, rep(NA, 13 - length(x))))
  }
  gffattr = as.data.frame(do.call(rbind, gffattr_list), stringsAsFactors = FALSE)

  ## get attributes names
  attrnames =  strsplit(dfraw[1,9],split=c("=|;"))[[1]][c(TRUE,FALSE)]
  colnames(gffattr) = attrnames

  gff_df$Final_Classification = gffattr$Final_Classification
  gff_df$Name = gffattr$Name
  gff_df$Region_Hits_Classifications = gffattr$Region_Hits_Classifications
  gff_df$Best_Hit = gffattr$Best_Hit
  gff_df$Best_Hit_DB_Pos = gffattr$Best_Hir_DB_Pos
  gff_df$DB_Seq = gffattr$DB_Seq
  gff_df$Query_Seq = gffattr$Query_Seq
  gff_df$Region_Seq = gffattr$Region_Seq
  gff_df$Identity = as.numeric(gffattr$Identity)
  gff_df$Similarity = as.numeric(gffattr$Similarity)
  gff_df$Relat_Length = as.numeric(gffattr$Relat_Length)
  gff_df$Relat_Interruptions = as.numeric(gffattr$Relat_Interruptions)
  gff_df$Hit_to_DB_Length = as.numeric(gffattr$Hit_to_DB_Length)
  return(gff_df)
}

gff = readGFF3fromDante(filepath)
# summarized_by = c("Final_Classification", "Name", "seqid")
# summarized_by = c("Final_Classification")


if (is.na(summarized_by)){
  ## export complete table
  write.table(gff, file = output, row.names = FALSE, quote = FALSE, sep = "\t")
}else{
  ## export summary
  tbl = data.frame(table(gff[, summarized_by]))
  write.table(tbl, file = output, row.names = FALSE, quote = FALSE, sep = "\t")
}
