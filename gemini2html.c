#include <stdio.h>
#include <string.h>

#define LINE_ENDING "\r\n"

int main(int argc,char *argv[]) {
  char line[65536];//65535+null
  char pre=0;
  char list=0;
  char *first;
  char *second;

  if(argc >= 2) {//if there's an argument, we output the header too.
    printf("<html><head><title>%s</title></head><body>%s",argv[1],LINE_ENDING);
  }

  while(fgets(line,sizeof(line)-1,stdin)) {
    //strip line endings ofc.
    if(first=strchr(line,'\r')) *first=0;
    if(first=strchr(line,'\n')) *first=0;

    if(!strncmp(line,"* ",2)) {
      first=line+2;
      if(!list) printf("<ul>%s",LINE_ENDING);
      list=1;
      printf("<li>%s</li>%s",first,LINE_ENDING);
      continue;
    }
    if(list) {//we didn't get a list item, but we're still in a list... close this shit up.
      printf("</ul>%s",LINE_ENDING);
      list=0;
    }
    if(!strncmp(line,"# ",2)) {
      first=line+2;
      printf("<h1>%s</h1>%s",first,LINE_ENDING);
      continue;
    }
    if(!strncmp(line,"## ",3)) {
      first=line+3;
      printf("<h2>%s</h2>%s",first,LINE_ENDING);
      continue;
    }
    if(!strncmp(line,"### ",4)) {
      first=line+4;
      printf("<h3>%s</h3>%s",first,LINE_ENDING);
      continue;
    }
    if(!strncmp(line,"```",3)) {
      first=line+3;
      pre^=1;
      if(pre) printf("<pre>");//this doesn't get a line ending on purpose. would insert an empty "preformatted" line.
      else printf("</pre>%s",LINE_ENDING);
      continue;
    }
    if(!strncmp(line,"=> ",3)) {
      first=line+3;
      if((second=strchr(first,' '))) {
        *second=0;
        second++;
      } else {
        second=first;
      }
      //need to encode the html entities for < > and "...
      printf("<a href=\"%s\">%s</a>%s%s",first,second,pre?"":"<br/>",LINE_ENDING);
      continue;
    }
    printf("%s%s%s",line,pre?"":"<br/>",LINE_ENDING);
  }
  if(list) printf("</ul>%s",LINE_ENDING);
  if(pre) printf("</pre>%s",LINE_ENDING);//gemini doesn't need it to be balanced, so we'll close it for html's sake.
  if(argc >= 2) printf("</body></html>%s",LINE_ENDING);//we output the header, let's finish it too.
}
