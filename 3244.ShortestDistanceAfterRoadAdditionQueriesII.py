from collections import deque


class Solution(object):
    explored = deque()
    visited = set([])

    def sumOfDistancesInTree(self, n, edges):
        graph = {node: [] for node in range(n)}
        ends = set([])
        distances = []

        for u, v in edges:
            ends.add(u)
            ends.add(v)
            graph[u].append(v)
            graph[v].append(u)

        for end in ends:
            distances.append(self.dfs_all_components(graph, end))

        result = []

        for distance in distances:
            count = 0
            for d in distance:
                count += d
            result.append(count)
        if len(result) == 0:
            result = [0]
        return result

    def dfs_all_components(self, adj, end):
        distances = []

        for node in adj:
            self.visited = set([])
            if node != end:
                distances.append(self.dfs_visit(adj, node, end))

        return distances

    def dfs_visit(self, adj, start=None, end=None, count=0):
        if start == end:
            return count

        self.visited.add(start)

        for neighbor in adj[start]:
            if neighbor not in self.visited:
                distance = self.dfs_visit(adj, neighbor, end, count + 1)
                if distance is not None:
                    return distance

        return None


def main():
    solution = Solution()
    distances = solution.sumOfDistancesInTree(
        6, [[0, 1], [0, 2], [2, 3], [2, 4], [2, 5]]
    )

    print(distances)


main()
