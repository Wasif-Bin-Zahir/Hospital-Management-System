#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

void clrscr(void)
{
    system("cls()");
}

void doc(void);
void menu(void);
void pat(void);
void test(void);


struct patient
{
    char name[40];
    int age;
    char bg[3];
    char gender;
    char regn[10];
    char doc_name[40];
    char history[200];
    char date[10];
    char ph[11];
};

struct doctor
{
    char name[40];
    int age;
    char bg[3];
    char gender;
    char id[10];
    char dept [20];
    char desig[40];
    char ph[11];
};

struct medtest
{
    int sno;
    char name[30];
    char adv[40];
    char gender;
    char bg[10];
    int age;
    char ph[20];
    char date [20];
    char doc_name[30];
    int qnty;
    float price;
    float amount;
};

void menu()
{
    char choice;
    printf("\n\n\n\n\n\n\n");
    printf("\t\t*************************************************");
    printf("\n\t\t******** DIGITAL APPOINTMENT SYSTEM ***********");
    printf("\n\t\t*************************************************");
    printf("\n\n\n\n\n\n\n");
    printf("\t\t1. PATIENT");
    printf("\n\t\t2. DOCTOR");
    printf("\n\t\t3. MEDICAL TEST");
    printf("\n\t\t0. EXIT");
    printf("\n\n\t\tEnter your choice: ");
    fflush(stdin);
    choice=getche();
    switch(choice)
    {
    case '1':
        pat();
        break;
    case '2':
        doc();
        break;
    case '3':
        test();
        break;
    case '0':
        exit(1);
    }
}//check


void main()
{
    system("COLOR E4");
    printf("\n\n\n\n\n");
    printf("\n\t\t********* WELCOME TO DIGITAL APPOINTMENT SYSTEM **************");
    printf("\n\n\n\n\n");
    printf("\t\tPlease sign in to use our system\n\n");
    while (1)
    {
wrong_id:
        printf("\t\tEnter your user id: ");
        char id[10];
        scanf ("%s",id);

        if(strcmp(id,"rahat")==0 || strcmp(id,"wasif")==0 ||strcmp(id,"new1")==0 ||strcmp(id,"new2")==0 ||strcmp(id,"new3")==0 )
        {
wrong_pass:
            printf("\t\tEnter your password: ");
            char pass[10];
            int i=0;
            char c;
            while(i<10)
            {
                pass[i]=getch();
                c=pass[i];
                if(c==13)
                    break;
                else
                    printf("*");
                i++;
            }
            pass[i]='\0';
            if(strcmp(pass,"12345")==0 ||strcmp(pass,"new1")==0)
            {
                break;
            }
            else
            {
                printf("\n\t\tYou have entered a wrong password. Try again\n");
                goto wrong_pass;
            }
        }

        else
        {
            printf ("\t\tYou have entered a wrong user id.\n");
            goto wrong_id;
        }
    }
    printf("You have signed in to the system successfully.\n");
    system("cls");                                                                                //window clear
    menu();
}
void pat()
{
    FILE *fp,*ft;                                                                 //fp patient file pointer, ft temp pointer
    char ch,another,z;
    char reg[20],pname[40],dname[40],idate[20];
    int i=0;
    long int recsize;
    struct patient p;
    fp=fopen("pat.DAT","rb+");
    if(fp==NULL)
    {
        fp=fopen("pat.DAT","wb+");
        if(fp==NULL)
        {
            puts("\nSorry!! Cannot open file");
            exit(1);
        }
    }
    recsize=sizeof(p);
    while(1)
    {
        clrscr();
        printf("\n\n\t\t\tPATIENT\n\n");
        printf("\n\t\t1. Place a new appointment");
        printf("\n\t\t2. Modify existing appointment data");
        printf("\n\t\t3. Search an appointment");
        printf("\n\t\t4. Listing of appointments");
        printf("\n\t\t5. Clear record");
        printf("\n\t\t6. Filter appointments by doctor's info");
        printf("\n\t\t7. Filter appointments by date");
        printf("\n\t\t8. Main menu");
        printf("\n\n\t\tEnter your choice here: ");
        fflush(stdin);
        ch=getche();
        switch(ch)
        {
         //###################### new case #########################
        case '1':                                                           //patient entry
            clrscr();
            fseek(fp,0,SEEK_END);
            another='Y';
            while(another=='Y'||another=='y')
            {
w:
                printf("\n\n\nEnter Appointment Number: ");
                scanf("%s",reg);
                rewind(fp);                                                  //file pointer at start
                while(fread(&p,recsize,1,fp)==1)
                {
                    if(strcmp(p.regn,reg)==0)
                    {
                        i=1;
                        printf("\n\t\tTHIS APPOINTMENT NUMBER ALREADY EXISTS. ENTER ANOTHER ONE");
                        goto w;
                    }
                }
                if(i==0||fread(&p,recsize,1,fp)==0)
                {
                    fseek (fp,0,SEEK_END);
                    strcpy(p.regn,reg);
                    fflush(stdin);
                    printf("\nEnter the name of the patient: ");
                    gets(p.name);
                    printf("\nEnter the gender of the patient(M.male or F.female): ");
                    scanf("%c",&p.gender);
                    fflush(stdin);
                    printf("\nEnter the age of the patient: ");
                    scanf("%d",&p.age);
                    fflush(stdin);
                    printf("\nEnter the phone number of the patient: ");
                    scanf("%s",p.ph);
                    fflush(stdin);
                    printf("\nHistory:");
                    gets(p.history);
                    printf("\nChoose a department\n\n1.Nuerology\n2.Pediatrics\n3.ENT\n4.Orthopedics\n5.Cardiology\n\n");
                    printf("Enter the name of a department:");
                    FILE *fs,*fx;
                    char more,c;
                    char id[20],s_name[40],dptname[40];
                    int iF=0;
                    long int recsize1;
                    struct doctor s;
                    fs=fopen("doc.DAT","rb+");
                    if(fs==NULL)
                    {
                        fs=fopen("doc.DAT","wb+");
                        if(fs==NULL)
                        {
                            puts("\nSorry!! Cannot open file");
                            exit(1);
                        }
                    }
                    recsize1=sizeof(s);
                    gets(dptname);
                    rewind(fs);
                    while(fread(&s,recsize1,1,fs)==1)
                    {
                        if(strcmp(s.dept,dptname)==0)
                        {
                            printf("\nRegistration number of the Doctor : ");
                            puts(s.id);
                            printf("\nName of the Doctor : ");
                            puts(s.name);
                            printf("\nAge : %d",s.age);
                            printf("\nGender : %c",s.gender);
                            printf("\nphone number : +88-%s\n",s.ph);
                            printf("\nQualifications : %s",s.desig);
                        }
                    }
                    fclose(fs);

                    printf("\nEnter the name of the Doctor to which he/she being referred: ");
                    gets(p.doc_name);
                    printf("\nDate dd/mm/yy: ");
                    scanf("%s",p.date);
                    fwrite(&p,recsize,1,fp);
                    printf("\n----------------------------------------------------");
                    printf("\nWant to add entry of the another Patient(Y/N): ");
                    fflush(stdin);
                    another=getche();
                }
            }
            break;

            //########################### new case ###############################

        case '2':                                                //modify patient data
            clrscr();
            another='Y';
            while(another=='Y'||another=='y')
            {
                printf("\nEnter the appointment number of the patient to modify: ");
                scanf("%s",reg);
                rewind(fp);
                while(fread(&p,recsize,1,fp)==1)
                {
                    if(strcmp(p.regn,reg)==0)
                    {
                        fflush(stdin);
                        printf("\nEnter the new name of the patient: ");
                        gets(p.name);
                        printf("\nEnter the new age of the patient: ");
                        scanf("%d",&p.age);
                        printf("\nEnter the new phone number of the patient: ");
                        scanf("%s",p.ph);
                        fflush(stdin);
                        printf("\nEnter the new history of the patient: ");
                        scanf("%s",p.history);
                        fflush(stdin);
                        printf("\nEnter the new date for appointment dd/mm/yy: ");
                        scanf("%s",p.date);
                        fflush(stdin);
                        fseek(fp,-recsize,SEEK_CUR);
                        fwrite(&p,recsize,1,fp);
                        break;
                    }
                }
                printf("\n----------------------------------------------------");
                printf("\nModify another Record(Y/N): ");
                fflush(stdin);
                another=getche();
            }
            break;

            //######################## new case ############################

        case '3':                                                      //search by appointment number
            clrscr();
            another='Y';
            while(another=='Y'||another=='y')
            {
                printf("\nEnter patient name to search: ");
                gets(pname);
                rewind(fp);
                while(fread(&p,recsize,1,fp)==1)
                {
                    if(strcmp(p.name,pname)==0)
                    {
                        printf("\nAppointment number of the patient : ");
                        puts(p.regn);
                        printf("\nName of the Patient : ");
                        puts(p.name);
                        printf("\nAge : %d",p.age);
                        printf("\nGender : %c",p.gender);
                        printf("\nphone number : +88%s",p.ph);
                        printf("\nEarlier History : ");
                        puts(p.history);
                        printf("\nName of the Doctor : ");
                        puts(p.doc_name);
                        printf("\nDate: %s",p.date);
                    }
                }//check
                printf("\n----------------------------------------------------");
                printf("\nSearch another Entry(Y/N): ");
                fflush(stdin);
                another=getche();
            }
            break;
        case '4':
            clrscr();
            rewind(fp);
            while(fread(&p,recsize,1,fp)==1)
            {
                printf("\nRegistration Number of the Patient : ");
                puts(p.regn);
                printf("\nName of the Patient : ");
                puts(p.name);
                printf("\nAge : %d",p.age);
                printf("\nGender : %c",p.gender);
                printf("\nphone number : %s\n",p.ph);
                printf("\nEarlier History : ");
                puts(p.history);
                printf("\nName of the Doctor : ");
                puts(p.doc_name);
                printf("\nDate: %s",p.date);
                printf("\n----------------------------------------------------\n");
            }
            getch();
            break;
        case '5':
            clrscr();
            another='Y';
            while(another=='Y'||another=='y')
            {
                printf("\nEnter any appointment number to delete the whole record: ");
                scanf("%s",reg);
                ft=fopen("temp.txt","wb+");
                rewind(fp);
                while(fread(&p,recsize,1,fp)==1)
                {
                    if(strcmp(p.regn,reg)!=0)
                        fwrite(&p,recsize,1,ft);
                    else
                        printf("\nThe Record has been Deleted Successfully.");
                }
                fclose(fp);
                fclose(ft);
                remove("pat.DAT");
                rename("temp.DAT","pat.DAT");
                fp=fopen("pat.DAT","rb+");
                printf("\nDelete another record?(Y/N): ");
                fflush(stdin);
                another=getche();
            }
            break;
        case '6':
            clrscr();
            another='Y';
            while(another=='Y'||another=='y')
            {
                printf("\nEnter doctor info to filter by: ");
                gets(dname);
                rewind(fp);
                while(fread(&p,recsize,1,fp)==1)
                {
                    if(strcmp(p.doc_name,dname)==0)
                    {
                        printf("\nAppointment Number of the Patient : ");
                        puts(p.regn);
                        printf("\nName of the Patient : ");
                        puts(p.name);
                        printf("\nAge : %d",p.age);
                        printf("\nGender : %c",p.gender);
                        printf("\nphone number : +88-%s",p.ph);
                        printf("\nEarlier History : ");
                        puts(p.history);
                        printf("\nName of the Doctor : ");
                        puts(p.doc_name);
                        printf("Date: %s",p.date);
                    }
                }//check
                printf("\n----------------------------------------------------");
                printf("\nSearch another Entry(Y/N): ");
                fflush(stdin);
                another=getche();
            }
            break;

            case '7':
            clrscr();
            another='Y';
            while(another=='Y'||another=='y')
            {
                printf("\nEnter date  to filter by: ");
                gets(idate);
                rewind(fp);
                while(fread(&p,recsize,1,fp)==1)
                {
                    if(strcmp(p.date,idate)==0)
                    {
                        printf("\nAppointment Number of the Patient : ");
                        puts(p.regn);
                        printf("\nName of the Patient : ");
                        puts(p.name);
                        printf("\nAge : %d",p.age);
                        printf("\nGender : %c",p.gender);
                        printf("\nphone number : +88-%s",p.ph);
                        printf("\nEarlier History : ");
                        puts(p.history);
                        printf("\nName of the Doctor : ");
                        puts(p.doc_name);
                        printf("Date: %s",p.date);
                    }
                }//check
                printf("\n----------------------------------------------------");
                printf("\nSearch another Entry(Y/N): ");
                fflush(stdin);
                another=getche();
            }
            break;

        case '8':
        {
            fclose(fp);
            clrscr();
            menu();
        }
        break;
        }
    }
}//check
void doc()
{
    FILE *fs,*fx;
    char more,c;
    char id[20],s_name[40],dptname[40];
    int iF=0;
    long int recsize1;
    struct doctor s;
    fs=fopen("doc.DAT","rb+");
    if(fs==NULL)
    {
        fs=fopen("doc.DAT","wb+");
        if(fs==NULL)
        {
            puts("\nSorry!! Cannot open file");
            exit(1);
        }
    }
    recsize1=sizeof(s);
    while(1)
    {
        clrscr();
        printf("\n\t\t\tDOCTOR\n\n");
        printf("\n\t\t1. Register a new doctor");
        printf("\n\t\t2. Modify registered doctor's data");
        printf("\n\t\t3. Search a doctor");
        printf("\n\t\t4. Listing of registered doctors");
        printf("\n\t\t5. Unregister a doctor");
        printf("\n\t\t6. Search doctors by departments");
        printf("\n\t\t7. Main Menu");
        printf("\n\n\t\tEnter your choice here: ");
        fflush(stdin);
        c=getche();
        switch(c)
        {
        case '1':
            clrscr();
            fseek(fs,0,SEEK_END);
            more='Y';
            while(more=='Y'||more=='y')
            {
u:
                printf("\n\n\nEnter the new registration number of the doctor: ");
                scanf("%s",id);
                rewind(fs);
                while(fread(&s,recsize1,1,fs)==1)
                {
                    if(strcmp(s.id,id)==0)
                    {
                        iF=1;
                        printf("\n\t\tTHIS REGISTRATION NUMBER ALREADY EXISTS. ENTER ANOTHER ONE");
                        goto u;
                    }
                }
                if(iF==0||fread(&s,recsize1,1,fs)==0)
                {
                    fseek (fs,0,SEEK_END);
                    strcpy(s.id,id);
                    fflush(stdin);
                    printf("\nEnter the name of the Doctor: ");
                    gets(s.name);
                    printf("\nEnter the gender of the doctor (M.male or F.female): ");
                    scanf("%c",&s.gender);
                    printf("\nEnter the Blood group of the Doctor: ");
                    scanf("%s",s.bg);
                    printf("\nEnter the age of the Doctor: ");
                    scanf("%d",&s.age);
                    printf("\nEnter the phone number of the Doctor: ");
                    scanf("%s",s.ph);
                    fflush(stdin);
                    printf("\nEnter the qualifications: ");
                    gets(s.desig);                                     //designation= qualification
                    printf("\nEnter the department: ");
                    scanf("%s",s.dept);
                    fwrite(&s,recsize1,1,fs);
                    printf("\n----------------------------------------------------");
                    printf("\nWant to register another Doctor(Y/N): ");
                    fflush(stdin);
                    more=getche();
                }
            }
            break;
        case '2':
            clrscr();
            more='Y';
            while(more=='Y'||more=='y')
            {
                printf("\nEnter the registration number of doctor to modify: ");
                scanf("%s",id);
                rewind(fs);
                while(fread(&s,recsize1,1,fs)==1)
                {
                    if(strcmp(s.id,id)==0)
                    {
                        fflush(stdin);
                        printf("\nEnter the new name of the doctor: ");
                        gets(s.name);
                        printf("\nEnter the new Blood group of the Doctor: ");
                        scanf("%s",s.bg);
                        printf("\nEnter the new age of the Doctor: ");
                        scanf("%d",&s.age);
                        printf("\nEnter the new phone number of the Doctor: ");
                        scanf("%s",s.ph);
                        fseek(fs,-recsize1,SEEK_CUR);
                        fwrite(&s,recsize1,1,fs);
                        break;
                    }
                }
                printf("\n----------------------------------------------------");
                printf("\nModify another Record(Y/N): ");
                fflush(stdin);
                more=getche();
            }
            break;//check
        case '3':
            clrscr();
            more='Y';
            while(more=='Y'||more=='y')
            {
                printf("\nEnter name to search: ");
                gets(s_name);
                rewind(fs);
                while(fread(&s,recsize1,1,fs)==1)
                {
                    if(strcmp(s.name,s_name)==0)
                    {
                        printf("\nRegistration number of the Doctor : ");
                        puts(s.id);
                        printf("\nName of the Doctor : ");
                        puts(s.name);
                        printf("\nAge : %d",s.age);
                        printf("\nAge : %d",s.dept);
                        printf("\nGender : %c",s.gender);
                        printf("\nBlood group: %s",s.bg);
                        printf("\nphone number : +88-%s\n",s.ph);
                        printf("\nQualifications : %s",s.desig);
                    }
                }
                printf("\n----------------------------------------------------");
                printf("\nSearch another Entry(Y/N): ");
                fflush(stdin);
                more=getche();
            }
            break;//check
        case '4':
            clrscr();
            rewind(fs);
            while(fread(&s,recsize1,1,fs)==1)
            {
                printf("\nRegistration number of the Doctor : ");
                puts(s.id);
                printf("\nName of the Doctor : ");
                puts(s.name);
                printf("\nAge : %d",s.age);
                printf("\nGender : %c",s.gender);
                printf("\nBlood group: %s",s.bg);
                printf("\nphone number : +88-%s\n",s.ph);
                printf("\nQualifications : %s",s.desig);
                printf("\n----------------------------------------------------\n");
            }
            getch();
            break;
        case '5':
            clrscr();
            more='Y';
            while(more=='Y'||more=='y')
            {
                printf("\nEnter the registration number of the Doctor to be deleted: ");
                scanf("%s",id);
                fx=fopen("tem.DAT","wb+");
                rewind(fs);
                while(fread(&s,recsize1,1,fs)==1)
                {
                    if(strcmp(s.id,id)!=0)
                        fwrite(&s,recsize1,1,fx);
                    else
                        printf("\nThe Record has been Deleted Successfully.");
                }
                fclose(fs);
                fclose(fx);
                remove("doc.DAT");
                rename("tem.DAT","doc.DAT");
                fs=fopen("doc.DAT","rb+");
                printf("\nDelete another record?(Y/N): ");
                fflush(stdin);
                more=getche();
            }
            break;//check
        case '6':
            clrscr();
            more='Y';
            while(more=='Y'||more=='y')
            {
                printf("\nEnter department to search: ");
                gets(dptname);
                rewind(fs);
                while(fread(&s,recsize1,1,fs)==1)
                {
                    if(strcmp(s.dept,dptname)==0)
                    {
                        printf("\nRegistration number of the Doctor : ");
                        puts(s.id);
                        printf("\nName of the Doctor : ");
                        puts(s.name);
                        printf("\nAge : %d",s.age);
                        printf("\nGender : %c",s.gender);
                        printf("\nBlood group: %s",s.bg);
                        printf("\nphone number : +88-%s\n",s.ph);
                        printf("\nQualifications : %s",s.desig);
                    }
                }
                printf("\n----------------------------------------------------");
                printf("\nSearch another Entry(Y/N): ");
                fflush(stdin);
                more=getche();
            }
            break;
        case '7':
        {
            fclose(fs);
            clrscr();
            menu();
        }
        break;
        }
    }
}//check
void test()                                           //#####################Medical Test########################
{
    FILE *fmt,*ft;
    char ch,another,z;
    char test[30],idate[20];
    int serial;
    int i=0;
    long int recsize;
    struct medtest m;
    fmt=fopen("medtest.DAT","rb+");
    if(fmt==NULL)
    {
        fmt=fopen("medtest.DAT","wb+");
        if(fmt==NULL)
        {
            puts("\nSorry!! Cannot open file");
            exit(1);
        }
    }
    recsize=sizeof(m);
    while(1)
    {
        clrscr();
        printf("\n\n\t\t\tMEDICAL TEST");
        printf("\n\t\t1. Book a test");
        printf("\n\t\t2. Listing of booked tests");
        printf("\n\t\t3. Clear whole record");
        printf("\n\t\t4. Filter by Test Name");
        printf("\n\t\t5. Filter by date");
        printf("\n\t\t6. Main menu");
        printf("\n\n\t\tEnter your choice here: ");
        fflush(stdin);
        ch=getche();
        switch(ch)
        {
        case '1':                                                           //test entry
            clrscr();
            fseek(fmt,0,SEEK_END);
            another='Y';
            while(another=='Y'||another=='y')
            {
w:
                printf("\n\n\nEnter Serial Number: ");
                scanf("%d",&serial);
                fflush(stdin);
                rewind(fmt);
                while(fread(&m,recsize,1,fmt)==1)
                {
                    if(serial==m.sno)
                    {
                        i=1;
                        printf("\n\t\tTHIS SERIAL NUMBER ALREADY EXISTS. ENTER ANOTHER ONE");
                        goto w;
                    }
                }
                if(i==0||fread(&m,recsize,1,fmt)==0)
                {
                    fseek (fmt,0,SEEK_END);
                    m.sno=serial;
                    printf("\nEnter the name of the patient: ");
                    gets(m.name);
                    printf("\nTest Name (Letters in capital): ");
                    scanf("%s",m.adv);
                    fflush(stdin);
                    printf("\nEnter the gender of the patient(M.male or F.female): ");
                    scanf("%c",&m.gender);
                    fflush(stdin);
                    printf("\nEnter the phone number of the patient: ");
                    scanf("%s",m.ph);
                    fflush(stdin);
                    printf("\nDate ddmmyy: ");
                    scanf("%s",m.date);
                    fflush(stdin);
                    printf("\nChoose a doctor who prescribed the test: ");
                    gets(m.doc_name);

                    //End of doctor choosing

                    fwrite(&m,recsize,1,fmt);
                    printf("\n----------------------------------------------------");
                    printf("\nDo you want to book another test?(Y/N): ");
                    fflush(stdin);
                    another=getche();
                }
            }
            break;

        case '2':
            clrscr();
            rewind(fmt);
            while(fread(&m,recsize,1,fmt)==1)
            {
                printf("\nSerial number: %d",m.sno);
                printf("\nName of the Patient : ");
                puts(m.name);
                printf("\nTest Name : %s",m.adv);
                printf("\nAge : %d",m.age);
                printf("\nGender : %c",m.gender);
                printf("\nBlood group: %s",m.bg);
                printf("\nPhone number : %s",m.ph);
                printf("\nDate ddmmyy : %s",m.date);
                printf("\nPrescribing doctor : ");
                puts(m.doc_name);
                printf("\n----------------------------------------------------\n");
            }
            getch();
            break;
        case '3':
            clrscr();
            another='Y';
            while(another=='Y'||another=='y')
            {
                printf("\nEnter any valid serial number to delete record: ");
                scanf("%d",&serial);
                ft=fopen("temp.txt","wb+");
                rewind(fmt);
                while(fread(&m,recsize,1,fmt)==1)
                {
                    if(serial=m.sno)
                        fwrite(&m,recsize,1,ft);
                    else
                        printf("\nThe Record has been Deleted Successfully.");
                }
                fclose(fmt);
                fclose(ft);
                remove("medtest.DAT");
                rename("temp.DAT","medtest.DAT");
                fmt=fopen("medtest.DAT","rb+");
                printf("\nDelete another record?(Y/N): ");
                fflush(stdin);
                another=getche();
            }
            break;
        case '4':
            clrscr();
            another='Y';
            while(another=='Y'||another=='y')
            {
                printf("\nEnter advise to filter by: ");
                gets(test);
                rewind(fmt);
                while(fread(&m,recsize,1,fmt)==1)
                {
                    if(strcmp(m.adv,test)==0)
                    {
                        printf("\nSerial number: %d",m.sno);
                        printf("\nName of the Patient : ");
                        puts(m.name);
                        printf("\nTest Name : %s",m.adv);
                        printf("\nAge : %d",m.age);
                        printf("\nGender : %c",m.gender);
                        printf("\nBlood group : %s",m.bg);
                        printf("\nPhone number : +88-%s",m.ph);
                        printf("\nDate : %s",m.date);
                        printf("\nPrescribing doctor : ");
                        puts(m.doc_name);
                    }
                }//check
                printf("\n----------------------------------------------------");
                printf("\nDo you want to search another?(Y/N): ");
                fflush(stdin);
                another=getche();
            }
            break;

            case '5':
            clrscr();
            another='Y';
            while(another=='Y'||another=='y')
            {
                printf("\nEnter date to filter by: ");
                gets(idate);
                rewind(fmt);
                while(fread(&m,recsize,1,fmt)==1)
                {
                    if(strcmp(m.date,idate)==0)
                    {
                        printf("\nSerial number: %d",m.sno);
                        printf("\nPatient Name : ");
                        puts(m.name);
                        printf("\nTest Name : %s",m.adv);
                        printf("\nAge : %d",m.age);
                        printf("\nGender : %c",m.gender);
                        printf("\nBlood group : %s",m.bg);
                        printf("\nPhone number : +88-%s",m.ph);
                        printf("\nDate : %s",m.date);
                        printf("\nPrescribing doctor : ");
                        puts(m.doc_name);
                    }
                }//check
                printf("\n----------------------------------------------------");
                printf("\nDo you want to search another?(Y/N): ");
                fflush(stdin);
                another=getche();
            }
            break;

        case '6':
        {
            fclose(fmt);
            clrscr();
            menu();
        }
        break;
        }
    }
}
