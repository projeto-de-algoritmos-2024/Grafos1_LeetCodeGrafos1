class Solution(object):
    count_components = 0

    def is_complete_component(self, component, adj):
        for node in component:
            if len(adj[node]) != len(component) - 1:
                return False
        return True

    def bfs(self, adj, start, explored):
        queue = [start]
        component = [start]
        explored.add(start)

        while queue:
            node = queue.pop(0)
            for neighbor in adj[node]:
                if neighbor not in explored:
                    explored.add(neighbor)
                    component.append(neighbor)
                    queue.append(neighbor)
        return component

    def bfs_all_components(self, adj):
        explored = set()

        for node in adj:
            if node not in explored:
                component = self.bfs(adj, node, explored)
                if self.is_complete_component(component, adj):
                    self.count_components += 1

    def countCompleteComponents(self, n, edges):
        self.count_components = 0

        graph = {i: [] for i in range(n)}
        for u, v in edges:
            graph[u].append(v)
            graph[v].append(u)

        self.bfs_all_components(graph)
        return self.count_components


def main():
    solution = Solution()
    result = solution.countCompleteComponents(6, [[0, 1], [0, 2], [1, 2], [3, 4]])
    print(result)


main()
