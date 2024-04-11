import random
import sys
from queue import Queue

def generate_map(width, height, walls):
	num_collectibles = max(1, (width * height) // 20)
	num_enemies = max(1, (width * height) // 50)
	#num_enemies = 1

	game_map = [['1' for _ in range(width)] for _ in range(height)]
	for i in range(1, height-1):
		for j in range(1, width-1):
			game_map[i][j] = '0'

	add_internal_walls(game_map, walls)

	placed = place_special_tiles(game_map, num_collectibles, num_enemies)
	if not placed:
		return generate_map(width, height, walls - 1)

	return game_map

def add_internal_walls(game_map, num_walls):
	height, width = len(game_map), len(game_map[0])
	for _ in range(num_walls):
		x, y = random.randint(1, height-2), random.randint(1, width-2)
		if game_map[x][y] == '0':
			game_map[x][y] = '1'

def place_special_tiles(game_map, num_collectibles, num_enemies):
	height = len(game_map)
	width = len(game_map[0])
	free_spaces = [(i, j) for i in range(1, height-1) for j in range(1, width-1) if game_map[i][j] == '0']
	random.shuffle(free_spaces)

	if len(free_spaces) < num_collectibles + 2:
		return False

	p_pos = free_spaces.pop()
	game_map[p_pos[0]][p_pos[1]] = 'P'

	e_pos = free_spaces.pop()
	game_map[e_pos[0]][e_pos[1]] = 'E'

	for _ in range(num_collectibles):
		c_pos = free_spaces.pop()
		game_map[c_pos[0]][c_pos[1]] = 'C'

	for _ in range(num_enemies):
		c_pos = free_spaces.pop()
		game_map[c_pos[0]][c_pos[1]] = 'X'

	if not is_accessible(game_map, p_pos, num_collectibles):
		return False

	return True

def is_accessible(game_map, start_pos, num_collectibles):
	height, width = len(game_map), len(game_map[0])
	visited = set()
	queue = Queue()
	queue.put(start_pos)
	visited.add(start_pos)
	collected = 0
	exit_found = False

	while not queue.empty() and not (collected == num_collectibles and exit_found):
		x, y = queue.get()
		for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
			nx, ny = x + dx, y + dy
			if 0 <= nx < height and 0 <= ny < width and (nx, ny) not in visited and game_map[nx][ny] != '1':
				visited.add((nx, ny))
				queue.put((nx, ny))
				if game_map[nx][ny] == 'C':
					collected += 1
					if collected == num_collectibles and exit_found:
						return True
				elif game_map[nx][ny] == 'E':
					exit_found = True
					if collected == num_collectibles and exit_found:
						return True

	return collected == num_collectibles and exit_found

def save_map_to_file(game_map, filename):
	with open(filename, "w") as file:
		height = len(game_map)
		for i, row in enumerate(game_map):
			if i < height - 1:
				file.write(''.join(row) + '\n')
			else:
				file.write(''.join(row))

if __name__ == "__main__":
	if len(sys.argv) < 4:
		print("Usage: script.py width height filename")
		sys.exit(1)

	width = int(sys.argv[1])
	height = int(sys.argv[2])
	filename = "./maps/" + sys.argv[3]

	game_map = generate_map(width, height, int((width * height) * 0.1))
	save_map_to_file(game_map, filename)
	print(f"Map generated and saved to {filename}. Dimensions: {width}x{height}")