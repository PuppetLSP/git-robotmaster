#include<iostream>
#include<cstdlib>
#include<cmath>
using namespace std;

//记录较小值
void recordSmall(int &small,int figure);

//求数组元素平均数
double sumupAverage(int arr[]);

//限制小数位
double limitDecimal(float d,int c);

//记录答案并返回用时
int getDuration(int &yoursum);

//生成随机数
int random(int s,int e);

//输出错题
void print_errors(int error_count,int errors[][6]);

int main()
{
    srand(time(NULL));//生成随机数种子
    
    int all_count,
        range,
        right_count=0,
        error_count=0,
        duration_min=-1,
        duration_all=0;
    float duration_average=0;
    //分是总题数，范围，对题数，错题数，最小时长，总时长, 平均时长
    
    cout << "请输入自定义题目数量: ";
    cin >> all_count;
    cout<< "请输入最大数:";
    cin >> range;
    int errors[all_count][6];//用于储存答错的题目题号及正确和错误答案
    int durations[all_count];//用于储存每道题的答题时长
    
    for(int i=0;i<all_count;i++)//循环执行all_count次
    {
        int first=random(1,range);//生成[1,range]区间的数
        int second=random(1,range);//同上
        int symbol_i=rand()%2;//生成0/1随机数代表运算符
        int right_sum=symbol_i==0?first+second:first-second;//记录正确结果
        char symbol=symbol_i==0?'+':'-';//根据数字判断实际运算符
        int your_sum;//用于记录输入的结果
        cout <<"第"<<i+1<<"题: "<<first<<" "<<symbol<<" "<<second<<" = ";
        
        int duration=getDuration(your_sum);//记录答案并获取用时
        
        durations[i]=duration;//记录答题时长(秒)
        
        recordSmall(duration_min,duration);//记录较小时长
        
        if(your_sum==right_sum)
            right_count++;//结果正确就将对题记录数加1
        else
        {
            error_count++;//错题记录数加1
            int index=error_count-1;//计算此次存放的索引
            errors[index][0]=i+1;//记录题号
            errors[index][1]=first;//记录第一个数
            errors[index][2]=second;//记录第二个数
            errors[index][3]=symbol_i;//记录运算符
            errors[index][4]=right_sum;//记录正确答案
            errors[index][5]=your_sum;//记录你的错误答案
        }
    }
    //答题结束
    duration_average=limitDecimal(sumupAverage(durations),1);//计算平均用时
    
    cout<<endl << "平均用时"<<duration_average<<"秒"<<endl<<"最短用时"<<duration_min<<"秒"<< endl;
    
    cout<<endl<< "此次共"<<all_count<<"道题，"
    <<"你答对了"<<right_count<<"题，"
    <<"答错了"<<error_count<<"题"<<endl<<endl;
    
    //输出答错的题
    print_errors(error_count,errors);

    return 0;
}

//记录较小值
void recordSmall(int &small,int figure)
{
    if(small==-1||figure<small)//判断是否第一次记录
        small=figure;
}

//求数组元素平均数
double sumupAverage(int arr[])
{
    float sum=0,count=sizeof(arr)/4;
    for(int i=0;i<count;i++)
        sum+=arr[i];
    return sum/count;
}

//限制小数位
double limitDecimal(float d,int c)
{
    return round(d*c*10)/c/10;
}

//记录答案并返回用时
int getDuration(int &yoursum)
{
    int time0=time(NULL);//获取答题前的时间
    cin >> yoursum;//将输入的答案放到your_sum中
    int time1=time(NULL);//获取答题后的时间
    return time1-time0;
}

//生成随机数
int random(int s,int e)
{
    return rand()%e+s;
}

//输出错题
void print_errors(int error_count,int errors[][6])
{
    if(error_count!=0)//如果有错题便输出
        cout<<"下面是你答错的"<<error_count<<"道题:"<<endl<<endl;
        
    for(int i=0;i<error_count;i++)
    {
        cout << "第"<<errors[i][0]<<"题: "<<errors[i][1]<<" "<<(errors[i][3]==0?'+':'-')<<" "<<errors[i][2]<<" = ?"<<endl
        <<"正确答案: "<<errors[i][4]<<endl
        <<"你的答案: "<<errors[i][5]<<endl<<endl;
    }
}
