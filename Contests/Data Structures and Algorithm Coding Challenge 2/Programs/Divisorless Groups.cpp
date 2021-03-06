#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <queue>
 
using namespace std;
 
const int MAX_N = 101, MAX_M = 25, MAX_MASK = (1 << 25);
map <int, int> visited;
 
int is_bit_set(int n, int bit)
{
    return ( (n& (1 << bit)) != 0);
}
 
int is_good_mask(int m)
{
    for(int bit = 1; bit <= MAX_M; bit++)
    {
        if(is_bit_set(m, bit - 1))
        {
            for(int multiple_bit = 2*bit; multiple_bit <= MAX_M; multiple_bit += bit)
            {
                if(is_bit_set(m, multiple_bit - 1))
                {
                    return false;
                }
            }
        }
    }
 
    return true;
}
 
int main()
{
    int no_of_people, no_of_skills;
    cin >> no_of_people >> no_of_skills;
 
    vector <int> profit(no_of_skills, 0);
    for(int i = 0; i < no_of_skills; i++)
    {
        cin >> profit[i];
    }
 
    vector <int> skillset(no_of_people + 1, 0);
    vector <int> profit_here(no_of_people + 1, 0);
    
    map <int, int> visited;
    queue <int> visitable_masks;
 
    for(int i = 1; i <= no_of_people; i++)
    {
        string skills;
        cin >> skills;
 
        profit_here[i] = 0;
 
        for(int bit = 0; bit < no_of_skills; bit++)
        {
            if(skills[bit] == '1')
            {
                skillset[i] |= (1 << bit);
 
                profit_here[i] += profit[bit];
            }
        }
        
        if(is_good_mask(skillset[i]))
        {
            visitable_masks.push(skillset[i]);
            
            visited[skillset[i]] = true;
        }
    }
 
    int answer = 0;
    while(!visitable_masks.empty())
    {
        int current_mask = visitable_masks.front();
        visitable_masks.pop();
        
        int current_profit = 0;
        for(int bit = 0; bit < no_of_skills; bit++)
        {
            if(is_bit_set(current_mask, bit))
            {
                current_profit += profit[bit];
            }
        }
        
        answer = max(answer, current_profit);
        
        for(int i = 1; i <= no_of_people; i++)
        {
            int new_mask = current_mask|skillset[i];
            
            if( ( (current_mask&skillset[i]) == 0) && is_good_mask(new_mask) && !visited[new_mask])
            {
                visitable_masks.push(new_mask);
                
                visited[new_mask] = true;
            }
        }
    }
    
    cout << answer;
    return 0;
}
