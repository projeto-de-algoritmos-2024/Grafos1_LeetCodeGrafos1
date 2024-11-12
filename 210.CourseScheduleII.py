class Solution:
    def findOrder(self, numCourses: int, prerequisites: List[List[int]]) -> List[int]:


        graph = []

        counter=[]

        candidate=[]

        order=[]


        for i in range(numCourses):
            graph.append([])
            counter.append(0)
        
        for prerequisite in prerequisites:
            u, v = prerequisite
            graph[v].append(u)
            counter[u]+=1
            if(v in graph[u] and u in graph[v]):
                return[]
        

        for i in range(numCourses):
            if(counter[i]==0):
                candidate.append(i)

        while(len(order)<numCourses):
        
            if(candidate==[] and len(order)<numCourses):
                return[]

            node=candidate.pop(0)
            for i in graph[node]:
                counter[i]-=1
            counter[node]=-1
            
            order.append(node)

            for i in range(numCourses):
                if(counter[i]==0 and i not in candidate):
                    candidate.append(i)

        return(order)