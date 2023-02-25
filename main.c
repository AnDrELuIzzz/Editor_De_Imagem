#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct pixel
{	int R, G, B;
} PIXEL;

void aumentarBrilho(PIXEL** original, int linhas, int colunas, int maxValor)
{	int l, c;
	for(l=0; l<linhas; l++)
	{	for(c=0; c<colunas; c++)
		{	original[l][c].R = (int)(original[l][c].R * 1.2);
			if(original[l][c].R > maxValor)
				original[l][c].R = maxValor;
			original[l][c].G = (int)(original[l][c].G * 1.2);
			if(original[l][c].G > maxValor)
				original[l][c].G = maxValor;
			original[l][c].B = (int)(original[l][c].B * 1.2);
			if(original[l][c].B > maxValor)
				original[l][c].B = maxValor;
		}
	}
}

void diminuirBrilho(PIXEL** original, int linhas, int colunas, int maxValor)
{	int l, c;
	for(l=0; l<linhas; l++)
	{	for(c=0; c<colunas; c++)
		{	original[l][c].R = (int)(original[l][c].R * 0.8);
			if(original[l][c].R > maxValor)
				original[l][c].R = maxValor;
			original[l][c].G = (int)(original[l][c].G * 0.8);
			if(original[l][c].G > maxValor)
				original[l][c].G = maxValor;
			original[l][c].B = (int)(original[l][c].B * 0.8);
			if(original[l][c].B > maxValor)
				original[l][c].B = maxValor;
		}
	}
}

void adicionaMoldura(PIXEL** imagem, int linhas, int colunas, int color ) {
    int l, c;
    int largura;

    printf("Digite a largura da moldura: ");
    scanf("%d", &largura);

    switch(color){
        case 1:
            for(l = 0; l < linhas; l++) {
                for(c = 0; c < colunas; c++) {
                    if(l < largura || l >= linhas - largura || c < largura || c >= colunas - largura) {
                        imagem[l][c].R = 0;
                        imagem[l][c].G = 0;
                        imagem[l][c].B = 0;
                    }
                }
            }
            break;
        case 2:
            for(l = 0; l < linhas; l++) {
                for(c = 0; c < colunas; c++) {
                    if(l < largura || l >= linhas - largura || c < largura || c >= colunas - largura) {
                        imagem[l][c].R = 255;
                        imagem[l][c].G = 255;
                        imagem[l][c].B = 255;
                    }
                }
            }
        default:
            printf("\nOpcao Invalida!");
            break

    }

}

void aumentarContraste(PIXEL** original, int linhas, int colunas, int maxValor) {
    int l, c, r, g, b;
    float fator;
    printf("\nDigite o fator de contraste: ");
    scanf("%f", &fator);
    double contraste = 255.0 / (255.0 - fator);
    for (l = 0; l < linhas; l++) {
        for (c = 0; c < colunas; c++) {
            r = (int)((original[l][c].R - fator / 2) * contraste);
            if (r < 0) {
                original[l][c].R = 0;
            } else if (r > maxValor) {
                original[l][c].R = maxValor;
            } else {
                original[l][c].R = r;
            }
            g = (int)((original[l][c].G - fator / 2) * contraste);
            if (g < 0) {
                original[l][c].G = 0;
            } else if (g > maxValor) {
                original[l][c].G = maxValor;
            } else {
                original[l][c].G = g;
            }
            b = (int)((original[l][c].B - fator / 2) * contraste);
            if (b < 0) {
                original[l][c].B = 0;
            } else if (b > maxValor) {
                original[l][c].B = maxValor;
            } else {
                original[l][c].B = b;
            }
        }
    }
}

void diminuirContraste(PIXEL** original, int linhas, int colunas, int maxValor) {
    int l, c, somaR = 0, somaG = 0, somaB = 0;
    double mediaR, mediaG, mediaB, fator = 1.5;

    // calcula a média de intensidade dos pixels da imagem
    for(l = 0; l < linhas; l++) {
        for(c = 0; c < colunas; c++) {
            somaR += original[l][c].R;
            somaG += original[l][c].G;
            somaB += original[l][c].B;
        }
    }
    mediaR = (double) somaR / (linhas * colunas);
    mediaG = (double) somaG / (linhas * colunas);
    mediaB = (double) somaB / (linhas * colunas);

    // aplica a transformação em cada pixel da imagem
    for(l = 0; l < linhas; l++) {
        for(c = 0; c < colunas; c++) {
            original[l][c].R = (int) ((original[l][c].R - mediaR) / fator + mediaR);
            original[l][c].G = (int) ((original[l][c].G - mediaG) / fator + mediaG);
            original[l][c].B = (int) ((original[l][c].B - mediaB) / fator + mediaB);

            // garante que os valores dos pixels estão dentro do intervalo [0, maxValor]
            if(original[l][c].R < 0)
                original[l][c].R = 0;
            if(original[l][c].G < 0)
                original[l][c].G = 0;
            if(original[l][c].B < 0)
                original[l][c].B = 0;

            if(original[l][c].R > maxValor)
                original[l][c].R = maxValor;
            if(original[l][c].G > maxValor)
                original[l][c].G = maxValor;
            if(original[l][c].B > maxValor)
                original[l][c].B = maxValor;
        }
    }
}

PIXEL** lerImagem(char * nomeArquivo, int *pLinhas, int *pColunas, int *pMaxValor)
{	FILE *fp;
	fp = fopen(nomeArquivo,"r");
	/* Arquivo ASCII, para leitura */
	if(!fp)
	{	printf( "\nErro na abertura do arquivo\n\n");
		exit(-1);
	}
	//leia tipo do arquivo
	char buffer[1001];
	fgets (buffer, 1000, fp); //Primeira linha
	if(strstr(buffer, "P3") == NULL) // o tipo de arquivo eh diferente de P3?
	{	printf( "\nErro no tipo do arquivo\n\n");
		exit(-2);
	}
	//leia comentario
	fgets (buffer, 1000, fp);

	//leia dados da imagem
	fscanf(fp, "%d%d%d", pColunas, pLinhas, pMaxValor);
	//criando a matriz
	PIXEL **mat;
	int i;
	mat = (PIXEL **) malloc(*pLinhas * sizeof(PIXEL *));
	for(i=0; i< *pLinhas; i++)
		mat[i] = (PIXEL *) malloc(*pColunas * sizeof(PIXEL));
	int l, c;
	for(l=0; l<*pLinhas; l++)
	{	for(c=0; c<*pColunas; c++)
		{	fscanf(fp, "%d", &mat[l][c].R);
			fscanf(fp, "%d", &mat[l][c].G);
			fscanf(fp, "%d", &mat[l][c].B);
		}
	}
	fclose(fp);
	return mat;
}
void escreverImagem(char * nomeArquivo, PIXEL ** mat, int linhas, int colunas, int maxValor)
{	FILE *fp;
	fp = fopen(nomeArquivo,"w");
	// Arquivo ASCII, para leitura
	if(!fp)
	{	printf( "\nErro na abertura do arquivo\n\n");
		exit(-1);
	}
	//escreva tipo do arquivo
	fprintf (fp, "P3\n");
	//escreva comentario
	fprintf (fp, "#Figura modificada...\n");
	//colunas, linhas
	fprintf(fp, "%d %d\n", colunas, linhas);
	//maxValor
	fprintf(fp, "%d\n", maxValor);
	int l, c;
	for(l=0; l<linhas; l++)
	{	for(c=0; c<colunas; c++)
			fprintf(fp, "%d\n%d\n%d\n", mat[l][c].R, mat[l][c].G, mat[l][c].B);
	}
	fclose(fp);
}
int main(int argc, char * argv[])
{	char opcao[10]="0";
	int linhas=0, colunas=0, maxValor=0;
	PIXEL **mat=NULL;
	int tamanhoBorrao = 8;
	char nomeArquivo[100]="";
	char nomeArquivoLeitura[100]="";
	char nomeArquivoEscrita[100]="";
	while(opcao[0] != '9')
	{	printf("\n\nMini-photoshop\n\n");
		printf("1) Ler imagem\n");
		printf("2) Gravar imagem\n");
		printf("3) Aumentar o brilho\n");
		printf("4) Diminuir o brilho\n");
		printf("5) Aumentar contraste\n");
		printf("6) Diminuir contraste\n");
		printf("7) Desfocar\n");
		printf("8) Fazer moldura\n");
		printf("9) Sair\n");
		printf("\nEntre a opcao desejada: ");
		fgets(opcao, 10, stdin);
		switch(opcao[0])
		{	case '1':
				printf("\n\nEntre com o nome da imagem (sem extensao): ");
				fgets(nomeArquivo, 100, stdin);
				nomeArquivo[strlen(nomeArquivo)-1]='\0';
				strcpy (nomeArquivoLeitura, nomeArquivo);
				strcat (nomeArquivoLeitura, ".ppm");
				mat = lerImagem(nomeArquivoLeitura, &linhas, &colunas, &maxValor);
				break;
			case '2':
				strcpy (nomeArquivoEscrita, nomeArquivo);
				strcat (nomeArquivoEscrita, "_editada.ppm");
				printf("\n\nA imagem sera salva como %s\n", nomeArquivoEscrita);
				escreverImagem(nomeArquivoEscrita, mat, linhas, colunas, maxValor);
				break;
			case '3':
				aumentarBrilho(mat, linhas, colunas, maxValor);
				break;
			case '4':
                mat =  diminuirBrilho(mat, linhas, colunas, maxValor);
				break;
			case '5':
				mat =  aumentarContraste(mat, linhas, colunas, maxValor);
				break;
			case '6':
				mat =  diminuirContraste(mat, linhas, colunas, maxValor);
				break;
			case '7':
				//mat =  borrar(mat, linhas, colunas, tamanhoBorrao);
				break;
			case '8':
			    int color;
				printf("\nDigite a cor da moldura: ");
				printf("\n1 - Preto");
				printf("\n2 - Branco\n");
				scanf("%d", &color);
				mat =  moldura(mat, linhas, colunas, maxValor, color);
				break;
		}
	}
	return 0;
}
