#include<stdio.h>
#include<stdlib.h>
int stringFound=0;
FILE *fp,*fp2;
void single_comment()
{
    char ch5;
    while((ch5=fgetc(fp))!=EOF)
    {
        if(ch5=='\n')
            return ;
    }
}
void block_comment()
{
    char ch3,ch4;
    while((ch3=fgetc(fp))!=EOF)
    {
        if(ch3=='*')
        {
            ch4=fgetc(fp);
            if(ch4=='/')
                return ;
        }
    }
}
void check_comment(char ch)
{
    char ch2;
    if(stringFound==1)
    {  
        if(ch=='"')
            stringFound=0;
        fputc(ch,fp2);
    }
    else if(stringFound==0 && ch=='"')
    {
        stringFound=1;
        fputc(ch,fp2);
    }
    else if(ch=='/')
    {
        if((ch2=fgetc(fp))=='*')
        {
            block_comment();
        }else if(ch2=='/')
        {
            single_comment();
        }else{
            fputc(ch,fp2);
            fputc(ch2,fp2);
        }
    }else{
        fputc(ch,fp2);
    }
}
int main(int argc,char *argv[])
{
    char ch;
    if(argc!=2)
    {
        printf("Usage remove.comments.c [file-name].txt");
        return 0;
    }
    fp=fopen(argv[1],"r");
    fp2=fopen("output.txt","w");
    while((ch=fgetc(fp))!=EOF)
    {
        check_comment(ch);
    }
    fclose(fp);
    fclose(fp2);
}