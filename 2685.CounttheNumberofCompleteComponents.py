class Solution(object):
    queue = []
    explored = []
    visited = []
    count_components = 0
    graph = {}

    def bfs_all_components(self, adj):
        for node in adj:
            if node in self.explored:
                # print(f"Nó: {node} já foi explorado")
                continue
            self.count_components += 1
            self.bfs(adj, node)
        return self.explored

    def bfs(self, adj, start=None, end=None):
        self.queue.append(start)
        self.visited.append(start)
        while self.queue:
            node = self.queue.pop(0)
            for neighbor in adj[node]:
                if neighbor == end:
                    return self.explored
                if neighbor not in self.explored:
                    self.explored.append(neighbor)
                    self.visited.append(neighbor)
                    self.queue.append(neighbor)

        return self.explored

    def is_complete(self, component, adj):
        for node in component:
            if len(adj[node]) != len(component) - 1:
                return False
        return True

    def countCompleteComponents(self, n, edges):
        if len(edges) == 0:
            return n

        graph = {i: [] for i in range(n)}
        for u, v in edges:
            graph[u].append(v)
            graph[v].append(u)

        self.bfs_all_components(graph)
        return self.count_components


def main():
    solution = Solution()
    result = solution.countCompleteComponents(2, [[1, 0]])
    # result == 3
    # [[0, 1],[0, 2],[1, 2],[3, 4]]
    # graph[0] = [1, 2]
    # graph[1] = [0, 2]
    # graph[2] = [0, 1]
    # #
    # graph[3] = [4]
    # graph[4] = [3]
    # #
    # graph[5] = []
    # bfs_all_components(graph)
    print(result)
    pass


main()
