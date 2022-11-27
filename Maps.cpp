int** mapSizeChange(int** mapMatrix, int height, int width, int lastheight)
{
	int** mapRem;
	mapRem = new int* [height];
	for (int i = 0; i < height; i++)
	{
		mapRem[i] = new int[width];
	}
	for (int i = 0; i < lastheight; i++)
	{
		delete[] mapMatrix[i];
	}
	delete[] mapMatrix;
	return mapRem;
}
