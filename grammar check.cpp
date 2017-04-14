
#include<stdio.h>
#include<malloc.h>
#include<conio.h>

#define LIMIT 500//specifies the maximum number of attempts the algorithm will make if the grammar
                    //can generate infinitely large sentences
#define NUMBER_OF_WORDS 11
#define NUMBER_OF_VARIABLES 7

typedef struct string_component{//represents a single word
    int index;
    bool is_terminal;
}string_component;


int input_string_size;
char *word_arr[NUMBER_OF_WORDS];//array storing all the terminal strings
char *var_arr[NUMBER_OF_VARIABLES];//array storing all the variable strings
string_component *input_string_by_index;//pointer to the entered string
string_component **production[NUMBER_OF_VARIABLES];//an array of pointers to an array
                                                //of pointers to an array of string_components
int number_of_productions[]={2,7,8,1,2,2,3};

//these are the variables used by the check function
int number_of_executions,variable_iterator;

void create_default_list(){
    //filling the terminal array
    word_arr[0]="like";
    word_arr[1]="plays";
    word_arr[2]="flies";
    word_arr[3]="time";
    word_arr[4]="dog";
    word_arr[5]="arrow";
    word_arr[6]="with";
    word_arr[7]="the";
    word_arr[8]="an";
    word_arr[9]="a";
    word_arr[10]="john";

    //filling the variable array
    var_arr[0]="<sentence>";
    var_arr[1]="<noun_phrase>";
    var_arr[2]="<verb_phrase>";
    var_arr[3]="<noun_phrase_with_determiner>";
    var_arr[4]="<preposition>";
    var_arr[5]="<prepositional_phrase>";
    var_arr[6]="<determiner>";
}

void create_default_grammar(){

    //an array of pointers to an array of sting_components has been assigned to productions one by one
    production[0]=(string_component**)(malloc(2*sizeof(string_component*)));
    production[1]=(string_component**)(malloc(7*sizeof(string_component*)));
    production[2]=(string_component**)(malloc(8*sizeof(string_component*)));
    production[3]=(string_component**)(malloc(1*sizeof(string_component*)));
    production[4]=(string_component**)(malloc(2*sizeof(string_component*)));
    production[5]=(string_component**)(malloc(2*sizeof(string_component*)));
    production[6]=(string_component**)(malloc(3*sizeof(string_component*)));

    //array of string_components is assigned to the pointers mentioned above
    production[0][0]=(string_component*)(malloc((2+1)*sizeof(string_component)));
    production[0][1]=(string_component*)(malloc((2+1)*sizeof(string_component)));

    production[1][0]=(string_component*)(malloc((1+1)*sizeof(string_component)));
    production[1][1]=(string_component*)(malloc((1+1)*sizeof(string_component)));
    production[1][2]=(string_component*)(malloc((1+1)*sizeof(string_component)));
    production[1][3]=(string_component*)(malloc((1+1)*sizeof(string_component)));
    production[1][4]=(string_component*)(malloc((2+1)*sizeof(string_component)));
    production[1][5]=(string_component*)(malloc((1+1)*sizeof(string_component)));
    production[1][6]=(string_component*)(malloc((1+1)*sizeof(string_component)));

    production[2][0]=(string_component*)(malloc((2+1)*sizeof(string_component)));
    production[2][1]=(string_component*)(malloc((2+1)*sizeof(string_component)));
    production[2][2]=(string_component*)(malloc((2+1)*sizeof(string_component)));
    production[2][3]=(string_component*)(malloc((1+1)*sizeof(string_component)));
    production[2][4]=(string_component*)(malloc((1+1)*sizeof(string_component)));
    production[2][5]=(string_component*)(malloc((1+1)*sizeof(string_component)));
    production[2][6]=(string_component*)(malloc((1+1)*sizeof(string_component)));
    production[2][7]=(string_component*)(malloc((1+1)*sizeof(string_component)));

    production[3][0]=(string_component*)(malloc((2+1)*sizeof(string_component)));

    production[4][0]=(string_component*)(malloc((1+1)*sizeof(string_component)));
    production[4][1]=(string_component*)(malloc((1+1)*sizeof(string_component)));

    production[5][0]=(string_component*)(malloc((2+1)*sizeof(string_component)));
    production[5][1]=(string_component*)(malloc((2+1)*sizeof(string_component)));

    production[6][0]=(string_component*)(malloc((1+1)*sizeof(string_component)));
    production[6][1]=(string_component*)(malloc((1+1)*sizeof(string_component)));
    production[6][2]=(string_component*)(malloc((1+1)*sizeof(string_component)));

    //filling out the values of the productions
    production[0][0][0].index=1;production[0][0][0].is_terminal=0;
    production[0][0][1].index=2;production[0][0][1].is_terminal=0;
    production[0][0][2].index=-1;production[0][0][2].is_terminal=0;

    production[0][1][0].index=3;production[0][1][0].is_terminal=0;
    production[0][1][1].index=2;production[0][1][1].is_terminal=0;
    production[0][1][2].index=-1;production[0][1][2].is_terminal=0;


    production[1][0][0].index=2;production[1][0][0].is_terminal=1;
    production[1][0][1].index=-1;production[1][0][1].is_terminal=1;

    production[1][1][0].index=5;production[1][1][0].is_terminal=1;
    production[1][1][1].index=-1;production[1][1][1].is_terminal=1;

    production[1][2][0].index=1;production[1][2][0].is_terminal=1;
    production[1][2][1].index=-1;production[1][2][1].is_terminal=1;

    production[1][3][0].index=4;production[1][3][0].is_terminal=1;
    production[1][3][1].index=-1;production[1][3][1].is_terminal=1;

    production[1][4][0].index=1;production[1][4][0].is_terminal=0;
    production[1][4][1].index=5;production[1][4][1].is_terminal=0;
    production[1][4][2].index=-1;production[1][4][2].is_terminal=0;

    production[1][5][0].index=10;production[1][5][0].is_terminal=1;
    production[1][5][1].index=-1;production[1][5][1].is_terminal=1;

    production[1][6][0].index=3;production[1][6][0].is_terminal=1;
    production[1][6][1].index=-1;production[1][6][1].is_terminal=1;


    production[2][0][0].index=2;production[2][0][0].is_terminal=0;
    production[2][0][1].index=1;production[2][0][1].is_terminal=0;
    production[2][0][2].index=-1;production[2][0][2].is_terminal=0;

    production[2][1][0].index=2;production[2][1][0].is_terminal=0;
    production[2][1][1].index=3;production[2][1][1].is_terminal=0;
    production[2][1][2].index=-1;production[2][1][2].is_terminal=0;

    production[2][2][0].index=2;production[2][2][0].is_terminal=0;
    production[2][2][1].index=5;production[2][2][1].is_terminal=0;
    production[2][2][2].index=-1;production[2][2][2].is_terminal=0;

    production[2][3][0].index=0;production[2][3][0].is_terminal=1;
    production[2][3][1].index=-1;production[2][3][1].is_terminal=1;

    production[2][4][0].index=1;production[2][4][0].is_terminal=1;
    production[2][4][1].index=-1;production[2][4][1].is_terminal=1;

    production[2][5][0].index=2;production[2][5][0].is_terminal=1;
    production[2][5][1].index=-1;production[2][5][1].is_terminal=1;

    production[2][6][0].index=3;production[2][6][0].is_terminal=1;
    production[2][6][1].index=-1;production[2][6][1].is_terminal=1;

    production[2][7][0].index=4;production[2][7][0].is_terminal=1;
    production[2][7][1].index=-1;production[2][7][1].is_terminal=1;


    production[3][0][0].index=6;production[3][0][0].is_terminal=0;
    production[3][0][1].index=1;production[3][0][1].is_terminal=0;
    production[3][0][2].index=-1;production[3][0][2].is_terminal=0;


    production[4][0][0].index=6;production[4][0][0].is_terminal=1;
    production[4][0][1].index=-1;production[4][0][1].is_terminal=1;

    production[4][1][0].index=0;production[4][1][0].is_terminal=1;
    production[4][1][1].index=-1;production[4][1][1].is_terminal=1;


    production[5][0][0].index=4;production[5][0][0].is_terminal=0;
    production[5][0][1].index=1;production[5][0][1].is_terminal=0;
    production[5][0][2].index=-1;production[5][0][2].is_terminal=0;

    production[5][1][0].index=1;production[5][1][0].is_terminal=0;
    production[5][1][1].index=3;production[5][1][1].is_terminal=0;
    production[5][1][2].index=-1;production[5][1][2].is_terminal=0;


    production[6][0][0].index=7;production[6][0][0].is_terminal=1;
    production[6][0][1].index=-1;production[6][0][1].is_terminal=1;

    production[6][1][0].index=8;production[6][1][0].is_terminal=1;
    production[6][1][1].index=-1;production[6][1][1].is_terminal=1;

    production[6][2][0].index=9;production[6][2][0].is_terminal=1;
    production[6][2][1].index=-1;production[6][2][1].is_terminal=1;

}

void create_custom_grammar(){
    }

void create_input_string(){


}

//-1 if not same;0 if same
int string_compare(string_component *mystring,int size){
    if(size!=input_string_size)
        return -1;
    for(int i=0;i<size;i++){
        if(mystring[i].index!=input_string_by_index[i].index||mystring[i].is_terminal!=input_string_by_index[i].is_terminal)
            return -1;
    }
    return 0;
}

//-1 if variable not present;returns index if present
int first_var_in_string(string_component *mystring,int size){
    int store=-1;
    for(int i=0;i<size;i++){
        if(mystring[i].is_terminal==0){
            store=i;
            break;
            }
    }
    return store;
}

string_component *create_copy(string_component *original, int size){
    string_component *new_string=(string_component*)(malloc(size*sizeof(string_component)));
    for(int i=0;i<size;i++){
        new_string[i].index=original[i].index;
        new_string[i].is_terminal=original[i].is_terminal;
    }
    return new_string;
}

void string_copy(string_component *copy,int copy_size,string_component *paste){
    if(copy_size<=0)
        return;
    for(int i=0;i<copy_size;i++){
        paste[i].index=copy[i].index;
        paste[i].is_terminal=copy[i].is_terminal;
    }
}

//returns the new size
string_component* insert_in_string(string_component *mystring,int size,int index_of_first_variable,int production_number){
    int size_of_prod=0;
    do{
        size_of_prod++;
    }
    while(production[index_of_first_variable][production_number][size_of_prod].index!=-1);
    string_component *new_string=(string_component*)(malloc((size + size_of_prod-1)*sizeof(string_component)));
    string_copy(mystring,index_of_first_variable,new_string);
    string_copy(production[index_of_first_variable][production_number],size_of_prod,new_string+index_of_first_variable);
    string_copy(mystring+index_of_first_variable+1,size - index_of_first_variable-1,new_string+index_of_first_variable+size_of_prod);
	//mystring=new_string;
	return new_string;
}

int new_size_after_insertion(int size,int index_of_first_variable,int production_number){
	int size_of_prod=0;
    do{
        size_of_prod++;
    }
    while(production[index_of_first_variable][production_number][size_of_prod].index!=-1);

	return (size + size_of_prod-1);
}

//returns 0 if matched;-1 if no match;-2 if limit crossed
int check(string_component *mystring,int size){
    //var_num
    int index_of_first_variable=-2,compare_result;
    if(number_of_executions<LIMIT){
        number_of_executions++;
		index_of_first_variable=mystring[first_var_in_string(mystring,size)].index;
        if(index_of_first_variable==-1){
            return string_compare(mystring,size);
        }
        else

            for(int production_number=0;production_number<number_of_productions[index_of_first_variable];){
                string_component *new_string=create_copy(mystring,size);//create new string
                //insert the production in the new string
				int new_size=new_size_after_insertion(size,index_of_first_variable,production_number);
                new_string=insert_in_string(new_string,size,index_of_first_variable,production_number);
                //send the new string into recursion
                switch(check(new_string,new_size))
                {
                    case 0:
                        return 0;
					case -2:
						return -2;
                }
                production_number++;
            }
			return -1;

    }
    else
        return -2;//limit reached;
}

void print_string(string_component *ptr, int size){
    printf("\n");
    for(int i=0;i<size;i++){
        if(ptr[i].is_terminal==true)
            printf("%s ",word_arr[ptr[i].index]);
        else
            printf("%s ",var_arr[ptr[i].index]);
    }
}

int main(){

    int i;
    create_default_list();
    create_default_grammar();

    //print the word dictionary
    printf("here is the list of valid words:\n");
    //print the dictionary
    for(i=0;i<NUMBER_OF_WORDS;i++){
        printf("%d. %s\n",i,word_arr[i]);
    }
    _getch();

    //take the input string from the user
    printf("\nEnter your sentence:\nHow many words would you enter?");
    scanf("%d",&input_string_size);
    input_string_by_index=(string_component*)(malloc(input_string_size*sizeof(string_component)));
    printf("enter your sentence(eg 3,2 means \"time flies\")\n");
    //take the sentence by index
    for(i=0;i<input_string_size;i++){
            printf("enter the %dth word's index",i+1);
            scanf("%d",&input_string_by_index[i].index);
            input_string_by_index[i].is_terminal=true;
        }
    printf("\nis this your sentence?(y/n)\n");
    //print the entered string
    print_string(input_string_by_index,input_string_size);

    if(getch()=='y'){//proceed if user says yes
        //create_input_string_list();
        printf("\npress enter to check whether sentence is valid:");
        getch();
        string_component *mystring=(string_component*)(malloc(sizeof(string_component)));
        mystring->index=0;
        mystring->is_terminal=0;
        switch(check(mystring,1)){
            case -2:
                printf("limit crossed");
                break;
			case -1:
                printf("\nstring is invalid");
                break;
			case 0:
                printf("\nstring is valid");
                break;
        }
    }
    else{//exit
        printf("\ngudbye");
    }
	_getch();
}
