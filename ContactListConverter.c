/*
	Conversor de Lista de Contatos
	Feito por Rulian Cruz: https://github.com/ruliancruz/ContactListConverter
	
	Um programa feito em C que seleciona todos os números de telefone contidos em uma lista de contatos
	exportada do Google Contacts em CSV e os ordena em coluna única em outro arquivo CSV.
	
	Para usá-lo coloque o arquivo que deseja converter na mesma pasta que esse programa com o nome igual o da constante CONTACT_LIST_IN
	
	Apenas números de contato que comecem com o caractere '+' serão convertidos
	
	O arquivo original será excluído após a execução do programa
*/

#include <stdio.h>
#include <locale.h>

#define CONTACT_LIST_IN "contacts.csv" //Arquivo original
#define CONTACT_LIST_ASSISTANT "contacts2.csv" //Arquivo Auxiliar
#define CONTACT_LIST_OUT "ContatosProntos.csv" //Arquivo final

void main()
{
	char character;
	char lineBreak = '\n';
	char space = ' ';
	int isAPhone;
	FILE *contactsIn;
	FILE *contactsOut;
	
	setlocale(LC_ALL, "Portuguese");
	
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
