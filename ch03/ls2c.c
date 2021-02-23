#include<stdio.h>
#include<dirent.h>      //for struct dirent
#include<sys/stat.h>    //for struct stat
#include<time.h>        //for ctime()
#include<pwd.h>         //for struct passwd
#include<grp.h>         //for struct group

#define MAXLEN 256

//函数声明
void do_ls(char[]);
void show_stat(char*,char*);
void show_file_info(char*,struct stat*);
char *uid_to_name(int);
char *gid_to_name(int);
void mode_to_letter(int,char[]);

int main(int ac,char* av[]){
    if(ac==1){
        do_ls(".");
    }
    else{
        while(--ac){
            do_ls(*++av);
        }
    }
    return 0;
}

void do_ls(char* dirname){
    DIR* dir;
    struct dirent* dirbufp;
    char* fullpath=(char*)malloc(strlen(dirname)+MAXLEN+1);
    if((dir=opendir(dirname))==NULL){
        //打开目录失败
        perror(dirname);
        exit(1);
    }
    else{
        while((dirbufp=readdir(dir))!=NULL){
            sprintf(fullpath, "%s/%s",dirname,dirbufp->d_name);
            show_stat(fullpath,dirbufp->d_name);
        }
        closedir(dir);
    }
}

void show_stat(char* fullpath,char* filename){
    struct stat info;
    if(stat(fullpath,&info)==-1)
        perror(filename);
    else
        show_file_info(filename,&info);
}

void show_file_info(char* filename, struct stat* info_p){
    char modestr[11];
    //将数值mode转为字符串mode
    mode_to_letter(info_p->st_mode,modestr);

    printf("%s",modestr);
    printf("%4d ",info_p->st_nlink);
    printf("%-8s ",uid_to_name(info_p->st_uid));
    printf("%-8s ",gid_to_name(info_p->st_gid));
    printf("%-8ld",info_p->st_size);
    printf("%.12s ",4+ctime(&info_p->st_mtime));
    printf("%s\n",filename);
}

void mode_to_letter(int mode,char str[]){

    strcpy(str,"----------");
    if(S_ISDIR(mode)) str[0]='d';
    if(S_ISCHR(mode)) str[0]='c';
    if(S_ISBLK(mode)) str[0]='b';

    if(mode & S_IRUSR) str[1]='r';
    if(mode & S_IWUSR) str[2]='w';
    if((mode & S_ISUID) && (mode & S_IXUSR)) str[3]='s';
    else if((mode & S_ISUID) && !(mode & S_IXUSR)) str[3]='S';
    else if(mode & S_IXUSR) str[3]='x';

    if(mode & S_IRGRP) str[4]='r';
    if(mode & S_IWGRP) str[5]='w';
    if((mode & S_ISGID) && (mode & S_IXGRP)) str[6]='s';
    else if((mode & S_ISGID) && !(mode & S_IXGRP)) str[6]='S';
    else if(mode & S_IXGRP) str[6]='x';

    if(mode & S_IROTH) str[7]='r';
    if(mode & S_IWOTH) str[8]='w';
    if((mode & S_ISVTX) && (mode & S_IXOTH)) str[9]='t';
    else if((mode & S_ISVTX) && !(mode & S_IXOTH)) str[9]='T';
    else if(mode & S_IXOTH) str[9]='x';
}

char* uid_to_name(int uid){
    struct passwd* pwd;
    char numstr[10];
    if((pwd=getpwuid(uid))==NULL){
        fprintf(numstr,"%d",uid);
        return numstr;
    }
    else{
        return pwd->pw_name;
    }
}

char* gid_to_name(int gid){
    struct group* grp_ptr;
    char numstr[10];
    if((grp_ptr=getgrgid(gid))==NULL){
        fprintf(numstr,"%d",gid);
        return numstr;
    }
    else
        return grp_ptr->gr_name;
}