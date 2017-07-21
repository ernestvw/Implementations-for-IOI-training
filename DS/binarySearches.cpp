// Binary Searches

int findIndex(vector<int> arr,int x) {
    int left=0,right=(int)arr.size()-1;
    while(left<=right) {
        int mid=(left+right)/2;
        if(arr[mid]<x) left=mid+1;
        else if(arr[mid]>x) right=mid-1;
        else return mid;
    }
    return -1;
}

int findBefore(vector<int> arr,int x) {
    if(arr.size()==0) return -1;
    if(arr[0]>x) return -1;
    int left=0,right=(int)arr.size()-1;
    while(left<=right) {
        int mid=(left+right)/2;
        if(arr[mid]<=x) left=mid+1;
        else if(arr[mid]>x) right=mid-1;
    }
    return left-1;
}

int findAfter(vector<int> arr,int x) {
    if(arr.size()==0) return -1;
    if(arr[(int)arr.size()-1]<x) return -1;
    int left=0,right=(int)arr.size()-1;
    while(left<=right) {
        int mid=(left+right)/2;
        if(arr[mid]<=x) left=mid+1;
        else if(arr[mid]>x) right=mid-1;
    }
    if(left>=arr.size()) return -1;
    return left;
}
