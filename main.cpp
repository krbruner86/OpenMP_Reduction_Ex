int main( int argc, char *argv[ ] )
{
  
  ...
    
	// NUMNODES*NUMNODES - (halfTileArea + 4)
	float fullTileArea = (  ( ( XMAX - XMIN )/(float)(NUMNODES-1) )  *
	                        ( ( YMAX - YMIN )/(float)(NUMNODES-1) )  );

	// NUMNODES - 2 * 4
	float halfTileArea = fullTileArea * .5;

	// 4
	float quarterTileArea = fullTileArea * .25;

	// sum up the weighted heights into the variable "volume"
	// using an OpenMP for loop and a reduction:

	double time0 = omp_get_wtime( );

	float volume = .0;

	#pragma omp parallel for collapse(2) default(none), shared(quarterTileArea, fullTileArea, halfTileArea) reduction(+: volume)
	for( int iv = 0; iv < NUMNODES; iv++ )
	{
		for( int iu = 0; iu < NUMNODES; iu++ )
		{
			float z = Height( iu, iv );
			if ((iv == 0 || iv == NUMNODES - 1) && (iu == 0 || iu == NUMNODES - 1)) {
				volume += (z * quarterTileArea);
			} else if ((iv != 0 && iv != NUMNODES - 1) && (iu != 0 && iu != NUMNODES - 1)) {
				volume += z * fullTileArea;
			} else {
				volume += (z * halfTileArea);
			}
		}
	}
  
  ...
}
