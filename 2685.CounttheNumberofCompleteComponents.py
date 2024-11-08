queue = []
explored = []
visited = []
count_components = 0
graph = {}


def bfs_all_components(adj):
    global count_components
    for node in adj:
        if node in explored:
            print(f"Nó: {node} já foi explorado")
            continue
        count_components += 1
        bfs(adj, node)
    return explored


def bfs(adj, start=None, end=None):
    global queue
    global explored
    global visited

    queue.append(start)
    visited.append(start)
    while queue:
        node = queue.pop(0)
        for neighbor in adj[node]:
            if neighbor == end:
                return explored
            if neighbor not in explored:
                explored.append(neighbor)
                visited.append(neighbor)
                queue.append(neighbor)

    return explored


def main():
    graph[0] = [1, 2]
    graph[1] = [0, 2]
    graph[2] = [0, 1]
    #
    graph[3] = [4]
    graph[4] = [3]
    #
    graph[5] = []
    bfs_all_components(graph)
    print(count_components)
    pass


main()
