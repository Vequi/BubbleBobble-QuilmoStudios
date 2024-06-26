#include "TileMap.h"
#include "Globals.h"
#include "ResourceManager.h"
#include <cstring>

TileMap::TileMap()
{
	map = nullptr;
	width = 0;
	height = 0;
	laser = nullptr;
	img_tiles = nullptr;
	img_objects = nullptr;

	InitTileDictionary();
}
TileMap::~TileMap()
{
	if (map != nullptr)
	{
		delete[] map;
		map = nullptr;
	}
	if (laser != nullptr)
	{
		laser->Release();
		delete laser;
		laser = nullptr;
	}
}
void TileMap::InitTileDictionary()
{
	const int n = TILE_SIZE;

	dict_rect[(int)Tile::L1BLOCK] = { 0, 2*n, n, n };
	dict_rect[(int)Tile::L1BLOCK_NUMT] = { n, 2*n, n, n};
	dict_rect[(int)Tile::L1BLOCK_NUMB] = { n, 3*n, n, n };

	dict_rect[(int)Tile::L1SHADE_RIGHT] = { 4*n, 12*n, n, n };
	dict_rect[(int)Tile::L1SHADE_CORNER] = { 2*n, 3*n, n, n };
	dict_rect[(int)Tile::L1SHADE_B] = { 3*n, 13*n, n, n };
	dict_rect[(int)Tile::L1SHADE_BD] = { 7*n, 13*n, n, n };
	dict_rect[(int)Tile::L1SHADE_CORNERB] = { 4*n, 13*n, n, n };
	dict_rect[(int)Tile::L1SHADE_3D] = { 2*n, 5*n, n, n };	
	
	dict_rect[(int)Tile::L6BLOCKTL] = { 0, 36*n, n, n };
	dict_rect[(int)Tile::L6BLOCKTR] = { n, 36*n, n, n };
	dict_rect[(int)Tile::L6BLOCKBL] = { 0, 37*n, n, n };
	dict_rect[(int)Tile::L6BLOCKBR] = { n, 37*n, n, n };
	dict_rect[(int)Tile::L6BLOCK_NUMT] = { n, 34*n, n, n};
	dict_rect[(int)Tile::L6BLOCK_NUMB] = { n, 35*n, n, n };
	dict_rect[(int)Tile::L6BLOCK_ALT] = { 2*n, 34*n, n, n };
						  
	dict_rect[(int)Tile::L6SHADE_RIGHT] = { 26*n, 44*n, n, n };
	dict_rect[(int)Tile::L6SHADE_CORNER] = { 2*n, 35*n, n, n };
	dict_rect[(int)Tile::L6SHADE_B] = { 3*n, 35*n, n, n };
	dict_rect[(int)Tile::L6SHADE_BD] = { 13*n, 35*n, n, n };
	dict_rect[(int)Tile::L6SHADE_CORNERB] = { 9*n, 35*n, n, n };
	dict_rect[(int)Tile::L6SHADE_3D] = { 2*n, 38*n, n, n };	
	
	dict_rect[(int)Tile::L34BLOCKTL] = { 0, 82*n, n, n };
	dict_rect[(int)Tile::L34BLOCK] = { 3*n, 62 * n, n, n };
	dict_rect[(int)Tile::L34BLOCK_NUMT1] = { 0, 66*n, n, n};
	dict_rect[(int)Tile::L34BLOCK_NUMT2] = { n, 66*n, n, n };	
	dict_rect[(int)Tile::L34BLOCK_NUMB1] = { 0, 67*n, n, n};
	dict_rect[(int)Tile::L34BLOCK_NUMB2] = { n, 67*n, n, n };

	dict_rect[(int)Tile::L34SHADE_RIGHT] = { 3*n, 67*n, n, n };
	dict_rect[(int)Tile::L34SHADE_CORNER] = { 2*n, 67*n, n, n };
	dict_rect[(int)Tile::L34SHADE_B] = { 2*n, 68*n, n, n };
	dict_rect[(int)Tile::L34SHADE_BD] = { 9*n, 67*n, n, n };
	dict_rect[(int)Tile::L34SHADE_CORNERB] = { 9*n, 69*n, n, n };
	dict_rect[(int)Tile::L34SHADE_3D] = { 13*n, 67*n, n, n };	
	
	dict_rect[(int)Tile::L46BLOCK] = { 0, 97 * n, n, n };
	dict_rect[(int)Tile::L46BLOCK_NUMT1] = { 0, 98 * n, n, n };
	dict_rect[(int)Tile::L46BLOCK_NUMT2] = { n, 98 * n, n, n };
	dict_rect[(int)Tile::L46BLOCK_NUMB1] = { 0, 99 * n, n, n };
	dict_rect[(int)Tile::L46BLOCK_NUMB2] = { n, 99 * n, n, n };
						  
	dict_rect[(int)Tile::L46SHADE_RIGHT] = { 4 * n, 99 * n, n, n };
	dict_rect[(int)Tile::L46SHADE_CORNER] = { 3 * n, 99 * n, n, n };
	dict_rect[(int)Tile::L46SHADE_B] = { 3 * n, 100 * n, n, n };
	dict_rect[(int)Tile::L46SHADE_BD] = { 6 * n, 102 * n, n, n };
	dict_rect[(int)Tile::L46SHADE_CORNERB] = { 4 * n, 102 * n, n, n };
	dict_rect[(int)Tile::L46SHADE_3D] = { 6 * n, 100 * n, n, n };	
	
	dict_rect[(int)Tile::L100BLOCK] = { 0, 129 * n, n, n };
	dict_rect[(int)Tile::L100BLOCK_NUMT1] = { 0, 130 * n, n, n };
	dict_rect[(int)Tile::L100BLOCK_NUMT2] = { n, 130 * n, n, n };
	dict_rect[(int)Tile::L100BLOCK_NUMB1] = { 0, 131 * n, n, n };
	dict_rect[(int)Tile::L100BLOCK_NUMB2] = { n, 131 * n, n, n };
						  
	dict_rect[(int)Tile::L100SHADE_RIGHT] = { 3 * n, 131 * n, n, n };
	dict_rect[(int)Tile::L100SHADE_CORNER] = { 2 * n, 131 * n, n, n };
	dict_rect[(int)Tile::L100SHADE_B] = { 2 * n, 132 * n, n, n };
	dict_rect[(int)Tile::L100SHADE_BD] = { 9 * n, 136 * n, n, n };
	dict_rect[(int)Tile::L100SHADE_CORNERB] = { 11 * n, 136 * n, n, n };
	dict_rect[(int)Tile::L100SHADE_3D] = { 11 * n, 135 * n, n, n };
	

	dict_rect[(int)Tile::BLOCK_SQUARE1_TL] = { 0,  0, n, n };
	dict_rect[(int)Tile::BLOCK_SQUARE1_TR] = { n,  0, n, n };
	dict_rect[(int)Tile::BLOCK_SQUARE1_BL] = { 0, n, n, n };
	dict_rect[(int)Tile::BLOCK_SQUARE1_BR] = { n, n, n, n };
	dict_rect[(int)Tile::BLOCK_SQUARE2_TL] = { 2 * n,  0, n, n };
	dict_rect[(int)Tile::BLOCK_SQUARE2_TR] = { 3 * n,  0, n, n };
	dict_rect[(int)Tile::BLOCK_SQUARE2_BL] = { 2 * n, n, n, n };
	dict_rect[(int)Tile::BLOCK_SQUARE2_BR] = { 3 * n, n, n, n };
	dict_rect[(int)Tile::BLOCK_VERT2_T] = { 4 * n,  0, n, n };
	dict_rect[(int)Tile::BLOCK_VERT2_B] = { 4 * n, n, n, n };
	dict_rect[(int)Tile::BLOCK_HORIZ2_L] = { 5 * n, 0, n, n };
	dict_rect[(int)Tile::BLOCK_HORIZ2_R] = { 6 * n, 0, n, n };
	dict_rect[(int)Tile::BLOCK_BLUE] = { 7 * n, 0, n, n };
	dict_rect[(int)Tile::BLOCK_HORIZ3_L] = { 5 * n, n, n, n };
	dict_rect[(int)Tile::BLOCK_HORIZ3_M] = { 6 * n, n, n, n };
	dict_rect[(int)Tile::BLOCK_HORIZ3_R] = { 7 * n, n, n, n };
	dict_rect[(int)Tile::BLOCK_BEAM_L] = { 0, 2 * n, n, n };
	dict_rect[(int)Tile::BLOCK_BEAM_R] = { n, 2 * n, n, n };

	dict_rect[(int)Tile::LADDER_L] = { 2 * n, 2 * n, n, n };
	dict_rect[(int)Tile::LADDER_R] = { 3 * n, 2 * n, n, n };
	dict_rect[(int)Tile::LADDER_TOP_L] = { 4 * n, 2 * n, n, n };
	dict_rect[(int)Tile::LADDER_TOP_R] = { 5 * n, 2 * n, n, n };

	dict_rect[(int)Tile::LOCK_RED] = { 6 * n, 2 * n, n, n };
	dict_rect[(int)Tile::LOCK_YELLOW] = { 7 * n, 2 * n, n, n };

	dict_rect[(int)Tile::LASER_L] = { 0, 6 * n, n, n };
	dict_rect[(int)Tile::LASER_R] = { 4 * n, 6 * n, n, n };
	
	dict_rect[(int)Tile::LASER_FRAME0] = { 1 * n, 6 * n, n, n };
	dict_rect[(int)Tile::LASER_FRAME1] = { 2 * n, 6 * n, n, n };
	dict_rect[(int)Tile::LASER_FRAME2] = { 3 * n, 6 * n, n, n };

}
AppStatus TileMap::Initialise()
{
	ResourceManager& data = ResourceManager::Instance();

	if (data.LoadTexture(Resource::IMG_TILES, "BubbleBobble_Art/Levels/VerticalLevels.png") != AppStatus::OK)
	{
		return AppStatus::ERROR;
	}
	img_tiles = data.GetTexture(Resource::IMG_TILES);

	if (data.LoadTexture(Resource::IMG_OBJECTS, "BubbleBobble_Art/Bubbles&Items/items.png") != AppStatus::OK)
	{
		return AppStatus::ERROR;
	}
	img_objects = data.GetTexture(Resource::IMG_OBJECTS);

	laser = new Sprite(img_tiles);
	if (laser == nullptr)
	{
		LOG("Failed to allocate memory for laser sprite");
		return AppStatus::ERROR;
	}
	laser->SetNumberAnimations(1);
	laser->SetAnimationDelay(0, ANIM_DELAY);
	laser->AddKeyFrame(0, dict_rect[(int)Tile::LASER_FRAME0]);
	laser->AddKeyFrame(0, dict_rect[(int)Tile::LASER_FRAME1]);
	laser->AddKeyFrame(0, dict_rect[(int)Tile::LASER_FRAME2]);
	laser->SetAnimation(0);

	return AppStatus::OK;
}
AppStatus TileMap::Load(int data[], int w, int h)
{
	size = w*h;
	width = w;
	height = h;

	if (map != nullptr)	delete[] map;

	map = new Tile[size];
	if (map == nullptr)	
	{
		LOG("Failed to allocate memory for tile map");
		return AppStatus::ERROR;
	}
	memcpy(map, data, size * sizeof(int));

	return AppStatus::OK;
}
void TileMap::Update()
{
	laser->Update();
}
Tile TileMap::GetTileIndex(int x, int y) const
{
	int idx = x + y*width;
	if(idx < 0 || idx >= size)
	{
		LOG("Error: Index out of bounds. Tile map dimensions: %dx%d. Given index: (%d, %d)", width, height, x, y)
		return Tile::AIR;
	}
	return map[x + y * width];
}
bool TileMap::IsTileSolid(Tile tile) const
{
	return (Tile::SOLID_FIRST <= tile && tile <= Tile::SOLID_LAST);
}
bool TileMap::IsTileLadderTop(Tile tile) const
{
	return tile == Tile::LADDER_TOP_L || tile == Tile::LADDER_TOP_R;
}
bool TileMap::IsTileLadder(Tile tile) const
{
	return tile == Tile::LADDER_L || tile == Tile::LADDER_R;
}
bool TileMap::TestCollisionWallLeft(const AABB& box) const
{
	return CollisionX(box.pos, box.height);
}
bool TileMap::TestCollisionWallRight(const AABB& box) const
{
	return CollisionX(box.pos + Point(box.width - 1, 0), box.height);
}
bool TileMap::TestCollisionGround(const AABB& box, int *py) const
{
	Point p(box.pos.x, *py);	//control point
	int tile_y;

	if (CollisionY(p, box.width))
	{
		tile_y = p.y / TILE_SIZE;

		*py = tile_y * TILE_SIZE - 1;
		return true;
	}
	return false;
}
bool TileMap::TestFalling(const AABB& box) const
{
	return !CollisionY(box.pos + Point(0, box.height), box.width);
}
bool TileMap::CollisionX(const Point& p, int distance) const
{
	int x, y, y0, y1;

	//Calculate the tile coordinates and the range of tiles to check for collision
	x = p.x / TILE_SIZE;
	y0 = p.y / TILE_SIZE;
	y1 = (p.y + distance - 1) / TILE_SIZE;
	
	//Iterate over the tiles within the vertical range
	for (y = y0; y <= y1; ++y)
	{
		//One solid tile is sufficient
		if (IsTileSolid(GetTileIndex(x, y)))
			return true;
	}
	return false;
}
bool TileMap::CollisionY(const Point& p, int distance) const
{
	int x, y, x0, x1;
	Tile tile;

	//Calculate the tile coordinates and the range of tiles to check for collision
	y = p.y / TILE_SIZE;
	x0 = p.x / TILE_SIZE;
	x1 = (p.x + distance - 1) / TILE_SIZE;

	//Iterate over the tiles within the horizontal range
	for (x = x0; x <= x1; ++x)
	{
		tile = GetTileIndex(x, y);

		//One solid or laddertop tile is sufficient
		if (IsTileSolid(tile) || IsTileLadderTop(tile))
			return true;
	}
	return false;
}
bool TileMap::TestOnLadder(const AABB& box, int* px) const
{
	int left, right, bottom;
	int tx1, tx2, ty;
	Tile tile1, tile2;
	
	//Control points
	left = box.pos.x;
	right = box.pos.x + box.width-1;
	bottom = box.pos.y + box.height-1;

	//Calculate the tile coordinates
	tx1 = left / TILE_SIZE;
	tx2 = right / TILE_SIZE;
	ty = bottom / TILE_SIZE;

	//To be able to climb up or down, both control points must be on ladder
	tile1 = GetTileIndex(tx1, ty);
	tile2 = GetTileIndex(tx2, ty);
	if (IsTileLadder(tile1) && IsTileLadder(tile2))
	{
		*px = GetLadderCenterPos(left, bottom) - box.width/2;
		return true;
	}
	return false;
}
bool TileMap::TestOnLadderTop(const AABB& box, int* px) const
{
	int left, right, bottom;
	int tx1, tx2, ty;
	Tile tile1, tile2;

	//Control points
	left = box.pos.x;
	right = box.pos.x + box.width - 1;
	bottom = box.pos.y + box.height - 1;

	//Calculate the tile coordinates
	tx1 = left / TILE_SIZE;
	tx2 = right / TILE_SIZE;
	ty = bottom / TILE_SIZE;

	//To be able to climb up or down, both control points must be on ladder
	tile1 = GetTileIndex(tx1, ty);
	tile2 = GetTileIndex(tx2, ty);
	if (IsTileLadderTop(tile1) && IsTileLadderTop(tile2))
	{
		*px = GetLadderCenterPos(left, bottom) - box.width / 2;
		return true;
	}
	return false;
}
int TileMap::GetLadderCenterPos(int pixel_x, int pixel_y) const
{
	int tx, ty;
	
	tx = pixel_x / TILE_SIZE;
	ty = pixel_y / TILE_SIZE;
	Tile tile = GetTileIndex(tx, ty);

	if (tile == Tile::LADDER_L || tile == Tile::LADDER_TOP_L)		return tx * TILE_SIZE + TILE_SIZE;
	else if (tile == Tile::LADDER_R || tile == Tile::LADDER_TOP_R)	return tx * TILE_SIZE;
	else
	{
		LOG("Internal error, tile should be a LADDER, coord: (%d,%d), tile type: %d", pixel_x, pixel_y, (int)tile);
		return 0;
	}
}
void TileMap::Render()
{
	Tile tile;
	Rectangle rc;
	Vector2 pos;

	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			tile = map[i * width + j];
			if (tile != Tile::AIR)
			{
				pos.x = (float)j * TILE_SIZE;
				pos.y = (float)i * TILE_SIZE;

				if (tile != Tile::LASER)
				{
					rc = dict_rect[(int)tile];
					DrawTextureRec(*img_tiles, rc, pos, WHITE);
				}
				else
				{
					laser->Draw((int)pos.x, (int)pos.y);
				}
			}
		}
	}
}
void TileMap::Release()
{
	ResourceManager& data = ResourceManager::Instance(); 
	data.ReleaseTexture(Resource::IMG_TILES);

	laser->Release();

	dict_rect.clear();
}