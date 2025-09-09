#include<iostream>
#include<map>
#include<set>
#include<string>

using namespace std;

void moveZeroes(vector<int>& nums) {
    int i = 0;
    while(i<nums.size())
    {
        if(nums[i]==0)
        {
            int j=i;
            while(j<nums.size())
            {
                if(nums[j]!=0) break;
                j++;
            }
            swap(nums[i],nums[j]);
        }
        i++;
    }
}
int main()
{
    vector<int> nums = {0,1,2,4,5,7};
    int i=0;
    while(i<nums.size())
    {
        string tmp = "";
        tmp+=to_string(nums[i]);
        
        for(int j = i+1;j<nums.size();j++)
        {
            if(nums[j]-nums[j-1]!=1)
            {
                tmp+="->";
                tmp+=to_string(nums[j-1]);
                i=j-1;
                break;
            }
        }
        i++;
    }
}
