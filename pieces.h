/* Shape of each piece is represented by rows in the array.
 * TIP: Name the array what is already been coded to avoid any unwanted errors.
 */
int BLOCKS[7][4] = {
					{0, 2, 4, 6},	// Shape 1
					{0, 1, 3, 5},	// Shape 2
					{1, 3, 4, 5},	// Shape 3
					{0, 1, 2, 3},	// Shape 4
					{1, 2, 3, 4},   // Shape 5
					{0, 2, 3, 5},	// Shape 6
					{1, 2, 3, 5},	// Shape 7
									};
					
int next_block[5][4] = {
					{0, 2, 4, 6},	// Shape 1
					{0, 1, 3, 5},	// Shape 2
					{0, 1, 2, 3},	// Shape 4
					{1, 2, 3, 4},   // Shape 5
					{1, 2, 3, 5},	// Shape 7
									};
