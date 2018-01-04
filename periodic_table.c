#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifndef NUMBER_OF_ELEMENTS
	#define NUMBER_OF_ELEMENTS 118
#endif

const char* categories[] = {"Alkali metals",
							"Alkaline earth metals",
							"Lanthanides",
							"Actinides",
							"Transition metals",
							"Post-transition metals",
							"Metalloid",
							"Nonmetals",
							"Halogens",
							"Noble gases"};
/*const int NUMBER_OF_ELEMENTS = 118;*/
const char* READ_MODE = "r"; 


typedef struct Element/*__attribute__((packed))*/
{
	int atomic_number;
	char symbol[2+1];
	char name[20+1];
	char atomic_mass[10+1];
	
	const char* categories[2];
	
	struct Element* next;
}element;

typedef struct 
{
	element* start;
}search_result;

typedef union  {
	int atomic_number;
	char symbol[2+1];
	char name [20+1];
	const char* category;
} search_criterion; 
typedef struct 
{
	search_criterion criterion;
	char search_by;
}search_request;
/*function proto types*/
/*void load_elements_by_file(element*,const char*);*/
void info();
void capitalize (char*);
void display (element*);
void search(element*, search_request*, search_result*);
void clear (element*);
int main(int argc, char* argv[])
{
	int i=0, idx=0;
	element elements[]=
	{
		{1,"H","Hydrogen","1.0079",{categories[7],NULL}},
		{2,"He","Helium","4.0026",{categories[9],NULL}},
		{3,"Li","Lithium","6.941",{categories[0],NULL}},//Group 1
		{4,"Be","Beryllium","9.0122",{categories[1],NULL}},//Group 2
		{5,"B","Boron","10.811",{categories[6],NULL}},
		{6,"C","Carbon","12.0107",{categories[7],NULL}},
		{7,"N","Nitrogen","14.0067",{categories[7],NULL}},
		{8,"O","Oxygen","15.9994",{categories[7],NULL}},
		{9,"F","Fluorine","18.9984",{categories[8],NULL}},
		{10,"Ne","Neon","20.1797",{categories[9],NULL}},
		{11,"Na","Sodium","22.9897",{categories[0],NULL}},//Group 1
		{12,"Mg","Magnesium","24.305",{categories[1],NULL}},//Group 2
		{13,"Al","Aluminum","26.9815",{categories[5],NULL}},
		{14,"Si","Silicon","28.0855",{categories[6],NULL}},
		{15,"P","Phosphorus","30.9738",{categories[7],NULL}},
		{16,"S","Sulfur","32.065",{categories[7],NULL}},
		{17,"Cl","Chlorine","35.453",{categories[8],NULL}},
		{18,"Ar","Argon","39.948",{categories[9],NULL}},
		{19,"K","Potassium","39.0983",{categories[0],NULL}},//Group 1
		{20,"Ca","Calcium","40.078",{categories[1],NULL}},//Group 2
		{21,"Sc","Scandium","44.9559",{categories[4],NULL}},
		{22,"Ti","Titanium","47.867",{categories[4],NULL}},
		{23,"V","Vanadium","50.9415",{categories[4],NULL}},
		{24,"Cr","Chromium","51.9961",{categories[4],NULL}},
		{25,"Mn","Manganese","54.938",{categories[4],NULL}},
		{26,"Fe","Iron","55.845",{categories[4],NULL}},
		{27,"Co","Cobalt","58.9332",{categories[4],NULL}},
		{28,"Ni","Nickel","58.6934",{categories[4],NULL}},
		{29,"Cu","Copper","63.546",{categories[4],NULL}},
		{30,"Zn","Zinc","65.39",{categories[4],NULL}},
		{31,"Ga","Gallium","69.723",{categories[5],NULL}},
		{32,"Ge","Germanium","72.64",{categories[6],NULL}},
		{33,"As","Arsenic","74.9216",{categories[6],NULL}},
		{34,"Se","Selenium","78.96",{categories[7],NULL}},
		{35,"Br","Bromine","79.904",{categories[8],NULL}},
		{36,"Kr","Krypton","83.8",{categories[9],NULL}},
		{37,"Rb","Rubidium","85.4678",{categories[0],NULL}},//Group 1
		{38,"Sr","Strontium","87.62",{categories[1],NULL}},//Group 2
		{39,"Y","Yttrium","88.9059",{categories[4],NULL}},
		{40,"Zr","Zirconium","91.224",{categories[4],NULL}},
		{41,"Nb","Niobium","92.9064",{categories[4],NULL}},
		{42,"Mo","Molybdenum","95.94",{categories[4],NULL}},
		{43,"Tc","Technetium","98",{categories[4],NULL}},
		{44,"Ru","Ruthenium","101.07",{categories[4],NULL}},
		{45,"Rh","Rhodium","102.9055",{categories[4],NULL}},
		{46,"Pd","Palladium","106.42",{categories[4],NULL}},
		{47,"Ag","Silver","107.8682",{categories[4],NULL}},
		{48,"Cd","Cadmium","112.411",{categories[4],NULL}},
		{49,"In","Indium","114.818",{categories[5],NULL}},
		{50,"Sn","Tin","118.71",{categories[5],NULL}},
		{51,"Sb","Antimony","121.76",{categories[6],NULL}},
		{52,"Te","Tellurium","127.6",{categories[6],NULL}},
		{53,"I","Iodine","126.9045",{categories[8],NULL}},
		{54,"Xe","Xenon","131.293",{categories[9],NULL}},
		{55,"Cs","Cesium","132.9055",{categories[0],NULL}},//Group 1
		{56,"Ba","Barium","137.327",{categories[1],NULL}},//Group 2
		{57,"La","Lanthanum","138.9055",{categories[2],categories[4]}},// Group 3
		{58,"Ce","Cerium","140.116",{categories[2],NULL}},// Group 3
		{59,"Pr","Praseodymium","140.9077",{categories[2],NULL}},// Group 3
		{60,"Nd","Neodymium","144.24",{categories[2],NULL}},// Group 3
		{61,"Pm","Promethium","145",{categories[2],NULL}},// Group 3
		{62,"Sm","Samarium","150.36",{categories[2],NULL}},// Group 3
		{63,"Eu","Europium","151.964",{categories[2],NULL}},// Group 3
		{64,"Gd","Gadolinium","157.25",{categories[2],NULL}},// Group 3
		{65,"Tb","Terbium","158.9253",{categories[2],NULL}},// Group 3
		{66,"Dy","Dysprosium","162.5",{categories[2],NULL}},// Group 3
		{67,"Ho","Holmium","164.9303",{categories[2],NULL}},// Group 3
		{68,"Er","Erbium","167.259",{categories[2],NULL}},// Group 3
		{69,"Tm","Thulium","168.9342",{categories[2],NULL}},// Group 3
		{70,"Yb","Ytterbium","173.04",{categories[2],NULL}},// Group 3
		{71,"Lu","Lutetium","174.967",{categories[2],NULL}},// Group 3
		{72,"Hf","Hafnium","178.49",{categories[4],NULL}},
		{73,"Ta","Tantalum","180.9479",{categories[4],NULL}},
		{74,"W","Tungsten","183.84",{categories[4],NULL}},
		{75,"Re","Rhenium","186.207",{categories[4],NULL}},
		{76,"Os","Osmium","190.23",{categories[4],NULL}},
		{77,"Ir","Iridium","192.217",{categories[4],NULL}},
		{78,"Pt","Platinum","195.078",{categories[4],NULL}},
		{79,"Au","Gold","196.9665",{categories[4],NULL}},
		{80,"Hg","Mercury","200.59",{categories[4],NULL}},
		{81,"Tl","Thallium","204.3833",{categories[5],NULL}},
		{82,"Pb","Lead","207.2",{categories[5],NULL}},
		{83,"Bi","Bismuth","208.9804",{categories[5],NULL}},
		{84,"Po","Polonium","209",{categories[6],NULL}},
		{85,"At","Astatine","210",{categories[8],NULL}},
		{86,"Rn","Radon","222",{categories[9],NULL}},
		{87,"Fr","Francium","223",{categories[0],NULL}},//Group 1
		{88,"Ra","Radium","226",{categories[1],NULL}},//Group 2
		{89,"Ac","Actinium","227",{categories[3],categories[4]}},
		{90,"Th","Thorium","232.0381",{categories[3],NULL}},
		{91,"Pa","Protactinium","231.0359",{categories[3],NULL}},
		{92,"U","Uranium","238.0289",{categories[3],NULL}},
		{93,"Np","Neptunium","237",{categories[3],NULL}},
		{94,"Pu","Plutonium","244",{categories[3],NULL}},
		{95,"Am","Americium","243",{categories[3],NULL}},
		{96,"Cm","Curium","247",{categories[3],NULL}},
		{97,"Bk","Berkelium","247",{categories[3],NULL}},
		{98,"Cf","Californium","251",{categories[3],NULL}},
		{99,"Es","Einsteinium","252",{categories[3],NULL}},
		{100,"Fm","Fermium","257",{categories[3],NULL}},
		{101,"Md","Mendelevium","258",{categories[3],NULL}},
		{102,"No","Nobelium","259",{categories[3],NULL}},
		{103,"Lr","Lawrencium","262",{categories[3],NULL}},
		{104,"Rf","Rutherfordium","261",{categories[4],NULL}},
		{105,"Db","Dubnium","262",{categories[4],NULL}},
		{106,"Sg","Seaborgium","266",{categories[4],NULL}},
		{107,"Bh","Bohrium","264",{categories[4],NULL}},
		{108,"Hs","Hassium","277",{categories[4],NULL}},
		{109,"Mt","Meitnerium","268",{categories[4],NULL}},
		{110,"Ds","Darmstadtium","?",{categories[4],NULL}},
		{111,"Rg","Roentgenium","272",{categories[4],NULL}},
		{112,"Cn","Copernicium","?",{categories[4],NULL}},
		{113,"Nh","Nihonium","?",{NULL,NULL}},
		{114,"Fl","Flerovium","?",{NULL,NULL}},
		{115,"Mc","Moscovium","?",{NULL,NULL}},
		{116,"Lv","Livermorium","?",{NULL,NULL}},
		{117,"Ts","Tennessine","?",{NULL,NULL}},
		{118,"Og","Oganesson","?",{categories[9],NULL}},

	};
	
	
	char choice = 'Y',search_by=0;
	element* temp;
	element* element_ptr=elements;
	/*
	element_ptr=(element*)malloc(NUMBER_OF_ELEMENTS* sizeof(element));
	load_elements_by_file(element_ptr, "./elements.txt");
	*/
	search_result result;
	
	search_request request;
	info();
	
	do{
		printf("\nPlease enter your search criterion?\n(A = Atomic Number, S = Symbol, N = Name, C = Category, D = Display): ");
		scanf(" %c",&search_by);
		search_by=toupper(search_by);
		request.search_by = search_by;
		
		switch(search_by)
		{
			case 'A':
				
				printf("Enter the atomic_number of the element you are interested in (1 - 118): ");
				scanf("%d",&(request.criterion.atomic_number));
				if(request.criterion.atomic_number<1 || request.criterion.atomic_number>NUMBER_OF_ELEMENTS)
					continue;
				
				search(element_ptr, &request, &result);
				break;
			case 'S':
				
				printf("Enter the symbol of the element you are interested in ( e.g. H or Li ): ");
				scanf("%s",request.criterion.symbol);
				capitalize(request.criterion.symbol);
				search(element_ptr, &request, &result);
				break;
			case 'N':
				
				printf("Enter the name of the element you are interested in ( e.g. Hydrogen or Lithium ): ");
				scanf("%s",request.criterion.name);
				capitalize(request.criterion.name);
				search(element_ptr, &request, &result);
				break;
			case 'D':
				printf("\n");
				display(element_ptr);
				break;
			case 'C':
						
				printf("\n");
				for(i=0;i<10;i++)
			    {
					printf("%d: %s\n", i+1, categories[i]);
			    }
				
				do
				{
					printf("Enter the  category you are interested in (1-10): ");
					scanf("%d",&idx);
				}
				while (idx<1 || idx>10);
				
				request.criterion.category = categories[idx-1]; /*substracting 1 to get the appropriate index*/
				search(element_ptr, &request, &result);
				break;
			default:
				continue;
		}
		
		temp=result.start;
		while(temp!=NULL){
		
			fprintf(stdout, "%d, %s, %s, %s", 
							temp->atomic_number, 
								temp->symbol, 
									temp->name,
										temp->atomic_mass);
			for(i=0;i<2;i++)
			{
				if (temp->categories[i]!=NULL)
				{
					fprintf(stdout, ", %s ",temp->categories[i]);
				}
			}
			fprintf(stdout,"\n");
			temp=temp->next;
		}
		clear(element_ptr);
		result.start=NULL;
		printf("\nDo you wish to continue? ");
		scanf(" %c",&choice);
	}
	while(toupper(choice)=='Y');
	/*free(element_ptr);*/
	return 0;
}
/*function defintion*/
void info(){
printf("  There are 118 different elements currently on the periodic table. Of the 118 elements that have\nbeen discovered, there are 90 elements (1 through 92 except for elements 43 and 61) that occur in\nnature in appreciable amounts. Elements are composed of atoms - atoms are comprised of protons\n(positively charged), neutrons (neutral) and electrons (negatively charged).\n\n  The atomic number or proton number of a chemical element is the number of protons found in the\nnucleus of an atom. It is identical to the charge number of the nucleus. The atomic number uniquely identifies a chemical element.\n\n  The atomic mass is the total number of protons and neutrons in the nucleus. It is the nucleus\nthat contributes to the mass of the atom. Each element has a unique symbol (an abbreviation).\nNatural elements have one or two letter chemical symbols; some manmade elements\nhave three-letter symbols.\n\n");
}
/*void load_elements_by_file(element* element_ptr, const char* file_name)
{
	FILE *file = NULL;
	
	
		
	file=fopen(file_name, READ_MODE);
	if(file!=NULL){
		
		fscanf(file, "%d%s%s%s", &(element_ptr->atomic_number), (element_ptr->symbol), (element_ptr->name),(element_ptr->atomic_mass));
		while(feof(file)==0){
			element_ptr++;
			fscanf(file, "%d%s%s%s", &(element_ptr->atomic_number), (element_ptr->symbol), (element_ptr->name),(element_ptr->atomic_mass));
		}
		fclose(file);
	}
	
	return;
}
*/
void capitalize (char* i){
	char * o = NULL;
	int counter=0;
	if(i!=NULL){
		o = i;
		while(*o){
			if(counter==0)
				*o = toupper(*o);
			else
				*o = tolower(*o);
			o++;
			counter++;
		}
	}
	return ;
	
}
void display (element* element_ptr){
	
	int counter=0,counter_lanthanides=0, counter_actinides=0;
	int a,period=0;
	element* actinides[15];
	element* lanthanides[15];
	printf("\n ");
	for (counter=1;counter<=18;counter++)
	{
		printf("%s%d ", (counter<10?"  ":" "),counter);
	}
	printf("\n\n");
	for (counter=0;counter<NUMBER_OF_ELEMENTS;counter++,element_ptr++)
	{
		a=element_ptr->atomic_number;
		
		
		if(a>=57&& a<=71)
		{
			if(a==57)
				printf("    ");
			lanthanides[counter_lanthanides] = element_ptr;
			counter_lanthanides++;
			continue;
		}
		if(a>=89&& a<=103)
		{
			if(a==89)
				printf("    ");
			actinides[counter_actinides] = element_ptr;
			counter_actinides++;
			continue;
		}
		if(a==1 || a==3 || a==11 || a==19 || a==37 || a==55 || a==87){
			period++;
			printf("%d %s%s ", period,(strlen(element_ptr->symbol)==1?" ":"") , element_ptr->symbol);
		}
		else
			printf(" %s%s ", (strlen(element_ptr->symbol)==1?" ":"") , element_ptr->symbol);
		
		if(a==1){
			printf("\t\t\t\t\t\t\t\t     ");
		}
		else if(a==4 || a==12){
			printf("\t\t\t\t\t ");
		}
		 
		if (a==2 || a==10 || a==18 || a==36 || a==54 || a==86 || a==118)
		{
			printf("\n");
		}
	}
	printf("\n");
	for (counter_lanthanides=0;counter_lanthanides<15;counter_lanthanides++)
	{
		a=lanthanides[counter_lanthanides]->atomic_number;
		if (a==57)
		{
			printf("\t     ");
		}
		printf(" %s%s ", (strlen(lanthanides[counter_lanthanides]->symbol)==1?" ":"") , lanthanides[counter_lanthanides]->symbol);
		if (a==71)
		{
			printf("\n");
		}
	}
	for (counter_actinides=0;counter_actinides<15;counter_actinides++)
	{
		
		a=actinides[counter_actinides]->atomic_number;
		if (a==89)
		{
			printf("\t     ");
		}
		printf(" %s%s ", (strlen(actinides[counter_actinides]->symbol)==1?" ":"") , actinides[counter_actinides]->symbol);
		if (a==103)
		{
			printf("\n");
		}
	}
	return;
}

void search(element* element_ptr, search_request* request_ptr, search_result* result_ptr)
{
	int i=0, j=0;
	element* temp=NULL;
	
	for(i=0;i<NUMBER_OF_ELEMENTS;i++){		
		switch(request_ptr->search_by)
		{
			case 'A':
				if(element_ptr->atomic_number==request_ptr->criterion.atomic_number){
					result_ptr->start = element_ptr;	
				}
				break;
			case 'S':
				if( strcmp(element_ptr->symbol,request_ptr->criterion.symbol)==0){
					result_ptr->start = element_ptr;
				}
				break;
			case 'N':
				if( strcmp(element_ptr->name,request_ptr->criterion.name)==0){
					result_ptr->start = element_ptr;
				}
				break;
			case 'C':
				for (j=0;j<2;j++)
				{
					/*printf("j=%d\n",j);*/
					if(element_ptr->categories[j]!=NULL){
						if( strcmp(element_ptr->categories[j],request_ptr->criterion.category)==0){
							/*printf("Category of element: %s\n",element_ptr->categories[j]);*/
							if(result_ptr->start==NULL){
								
								temp=result_ptr->start = element_ptr;
							}
							else{
								temp->next=element_ptr;
								temp=temp->next;
							}
						}
					}
				}
				break;
			default:
				break;
		}
	
		element_ptr++;
	}
	return;
}
void clear (element* element_ptr){
	int i=0;
	for(i=0;i<NUMBER_OF_ELEMENTS;i++){
		element_ptr->next=NULL;
		element_ptr++;
	}
}