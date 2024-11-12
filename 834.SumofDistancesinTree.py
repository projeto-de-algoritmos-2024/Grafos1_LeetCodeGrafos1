from collections import deque


class Solution(object):
    explored = deque()
    visited = set([])

    def sumOfDistancesInTree(self, n, edges):
        graph = {node: [] for node in range(n)}
        result = [0] * n
        count = [1] * n

        for u, v in edges:
            graph[u].append(v)
            graph[v].append(u)

        def dfs(node, parent):
            for neighbor in graph[node]:
                if neighbor != parent:
                    dfs(neighbor, node)
                    count[node] += count[neighbor]
                    result[node] += result[neighbor] + count[neighbor]

        def dfs2(node, parent):
            for neighbor in graph[node]:
                if neighbor != parent:
                    result[neighbor] = (
                        result[node] - count[neighbor] + (n - count[neighbor])
                    )
                    dfs2(neighbor, node)

        dfs(0, -1)
        dfs2(0, -1)
        return result


def main():
    solution = Solution()
    distances = solution.sumOfDistancesInTree(
        6, [[0, 1], [0, 2], [2, 3], [2, 4], [2, 5]]
    )

    print(distances)


main()
