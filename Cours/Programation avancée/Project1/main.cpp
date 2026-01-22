#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include <windows.h>


int main()
{
	FILE* pFile = NULL;

	errno_t err = fopen_s(&pFile, "Capybara.bmp", "rb");

	if (err != 0)
	{
		std::cout << "Erreur";
		return 1;
	}

	BITMAPFILEHEADER fileHeader;
	BITMAPINFOHEADER infoHeader;

	fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, pFile);
	fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, pFile);

	std::cout << "Hauteur: " << infoHeader.biHeight << "\n Largeur: " << infoHeader.biWidth << "\n Bits: " << infoHeader.biBitCount << std::endl;

	fseek(pFile, fileHeader.bfOffBits, 0);

	size_t pixelArraySize = infoHeader.biSizeImage;

	unsigned char* pixelData = (unsigned char*)malloc(pixelArraySize);


	fread(pixelData, 1, pixelArraySize, pFile);

	fclose(pFile);

	for (size_t i = 0; i < pixelArraySize; i += 3)
	{
		unsigned char tmp = pixelData[i];
		pixelData[i] = pixelData[i + 2];
		pixelData[i + 2];
	}

	FILE* pOut = NULL;
	err = fopen_s(&pOut, "NewCapybara.bmp", "wb");

	if (err != 0)
	{
		std::cout << "Erreur";
		return 1;
	}

	fwrite(&fileHeader, sizeof(BITMAPFILEHEADER), 1, pOut);
	fwrite(&infoHeader, sizeof(BITMAPINFOHEADER), 1, pOut);

	fwrite(pixelData, 1, pixelArraySize, pOut);

	fclose(pOut);

	free(pixelData);

	std::cout << "Nouveau fichier cree";
}