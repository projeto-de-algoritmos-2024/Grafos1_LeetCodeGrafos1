class Solution:
    def secondMinimum(self, n: int, edges: List[List[int]], time: int, change: int) -> int:
        second = -1
        timeTaken = 0

        
        graph = []

        for i in range(n+1):
            graph.append([])
        
        for edge in edges:
            u, v = edge
            graph[u].append(v)
            graph[v].append(u)

        queue = []
        dist1 = [-1] * (n + 1)
        dist2 = [-1] * (n + 1)

        queue.append([1, 1])
        dist1[1] = 0

        while len(queue)>0:
            node,freq = queue.pop(0)

            timeTaken = dist1[node] if freq == 1 else dist2[node]
            if (timeTaken // change) % 2:
                timeTaken = change * (timeTaken // change + 1) + time
            else:
                timeTaken += time

            neighbors = graph[node]
            for neighbor in neighbors:
                if dist1[neighbor] == -1:
                    dist1[neighbor] = timeTaken
                    queue.append([neighbor, 1])
                elif dist2[neighbor] == -1 and dist1[neighbor] != timeTaken:
                    dist2[neighbor] = timeTaken
                    queue.append([neighbor, 2])
                    if neighbor == n:
                        if second == -1:
                            second = timeTaken
                        elif timeTaken < second:
                            second = timeTaken

        return second
