float MAXGeneratedPackets(float R,float D,int M,float U ,int display=1)
{
	float i = (float)R / (D*M*U);
	if (display == 1)
	{
		cout << "¦Ëc: " << i << endl;
	}
	return i;
}