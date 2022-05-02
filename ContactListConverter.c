/*
	Conversor de Lista de Contatos
	Feito por Rulian Cruz: 
*/
#include <stdio.h>
#include <locale.h>
#include <string.h>

#define CONTACT_LIST_IN "contacts.csv"
#define CONTACT_LIST_ASSISTANT "contacts2.csv"
#define CONTACT_LIST_OUT "ContatosProntos.csv"

void main()
{
	char character;
	char lineBreak = '\n';
	char space = ' ';
	int isAPhone;
	FILE *contactsIn;
	FILE *contactsOut;
	
	setlocale(LC_ALL, "Portuguese");
	//contactsIn = fopen(CONTACT_LIST_IN, "r");
	
	if(!(contactsIn = fopen(CONTACT_LIST_IN, "r")))
	{
		printf("Não existe nenhum arquivo chamado %s na pasta.\n", CONTACT_LIST_IN);
		printf("Por favor, insira a lista de contatos na pasta com o nome correto.");
		fclose(contactsIn);
		return;
	}
	
	contactsOut = fopen(CONTACT_LIST_ASSISTANT, "w");
	fread(&character, sizeof(character), 1, contactsIn);
				
	while(!feof(contactsIn))
	{
		fread(&character, sizeof(character), 1, contactsIn);
		
		if(character == ',' && isAPhone == 0)
			isAPhone = 1;
		
		if(character == '+')
		{
			if(isAPhone == 1)
			{
				while(character != ',')
				{
					fwrite(&character, sizeof(character), 1, contactsOut);
					fread(&character, sizeof(character), 1, contactsIn);
				}
				
				fwrite(&lineBreak, sizeof(character), 1, contactsOut);
			}
			
			isAPhone = 0;
		}
	}
	
	fclose(contactsIn);
	fclose(contactsOut);
	remove(CONTACT_LIST_IN);
	
	contactsIn = fopen(CONTACT_LIST_ASSISTANT, "r");
	contactsOut = fopen(CONTACT_LIST_OUT, "w");
	fread(&character, sizeof(character), 1, contactsIn);
	fwrite(&character, sizeof(character), 1, contactsOut);
	
	while(!feof(contactsIn))
	{
		fread(&character, sizeof(character), 1, contactsIn);
		
		if(character == ' ')
		{
			fread(&character, sizeof(character), 1, contactsIn);
				
			if(character == ':')
			{
				fread(&character, sizeof(character), 1, contactsIn);
				
				if(character == ':')
				{
					fread(&character, sizeof(character), 1, contactsIn);
					
					if(character == ':')
					{
						fwrite(&lineBreak, sizeof(lineBreak), 1, contactsOut);
						fread(&character, sizeof(character), 1, contactsIn);
						fread(&character, sizeof(character), 1, contactsIn);
					}
				}
			}
			else
				fwrite(&space, sizeof(space), 1, contactsOut);
		}
		
		fwrite(&character, sizeof(character), 1, contactsOut);
	}
	
	fclose(contactsIn);
	fclose(contactsOut);
	remove(CONTACT_LIST_ASSISTANT);
	printf("A conversão foi concluída.");
}
