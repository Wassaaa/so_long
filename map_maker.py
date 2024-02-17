import random
import sys
from queue import Queue

def generate_map(width, height):
	num_collectibles = max(1, (width * height) // 20)
	
	game_map = [['1' for _ in range(width)] for _ in range(height)]
	for i in range(1, height-1):
		for j in range(1, width-1):
			game_map[i][j] = '0'

	add_internal_walls(game_map, int((width * height) * 0.2))

	placed = place_special_tiles(game_map, num_collectibles)
	if not placed:
		return generate_map(width, height)  # Retry if placement fails

	return game_map

def add_internal_walls(game_map, num_walls):
	height, width = len(game_map), len(game_map[0])
	for _ in range(num_walls):
		x, y = random.randint(1, height-2), random.randint(1, width-2)
		if game_map[x][y] == '0':  # Ensure we don't overwrite special tiles
			game_map[x][y] = '1'

def place_special_tiles(game_map, num_collectibles):
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
	
	if not is_accessible(game_map, p_pos):
		return False
	
	return True

def is_accessible(game_map, start_pos):
	# BFS to check if all collectibles and the exit are accessible
	height, width = len(game_map), len(game_map[0])
	visited = [[False for _ in range(width)] for _ in range(height)]
	queue = Queue()
	queue.put(start_pos)
	visited[start_pos[0]][start_pos[1]] = True
	targets = {'C': 0, 'E': False}
	
	while not queue.empty():
		x, y = queue.get()
		for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
			nx, ny = x + dx, y + dy
			if 0 <= nx < height and 0 <= ny < width and not visited[nx][ny] and game_map[nx][ny] != '1':
				visited[nx][ny] = True
				queue.put((nx, ny))
				if game_map[nx][ny] == 'C':
					targets['C'] += 1
				elif game_map[nx][ny] == 'E':
					targets['E'] = True
	
	# Check if all conditions met (at least one collectible and one exit found)
	return targets['C'] >= 1 and targets['E']

def save_map_to_file(game_map, filename="map.ber"):
    with open(filename, "w") as file:
        height = len(game_map)
        for i, row in enumerate(game_map):
            if i < height - 1:
                file.write(''.join(row) + '\n')
            else:
                file.write(''.join(row))

if __name__ == "__main__":
	if len(sys.argv) < 3:
		print("Usage: script.py width height")
		sys.exit(1)
	
	width = int(sys.argv[1])
	height = int(sys.argv[2])
	
	game_map = generate_map(width, height)
	save_map_to_file(game_map)
	print(f"Map generated and saved to map.ber. Dimensions: {width}x{height}")