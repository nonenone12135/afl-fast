#include "sort.h"

//自定义排序
struct comp {
    bool operator ()(const DP& dpl, const DP& dpr) {
        return (dpl.distance >= dpr.distance); //这个是从大到小,距离一样
    }
};

//struct comp {
//    bool operator ()(const DP& dpl, const DP& dpr) {
//        return (dpl.distance >= dpr.distance);
//    }
//};

set<DP,comp> dis_list; // 记录所有的轨迹, 这个在c中没法调用 对于元素是自定义的结构体,还需要重写排序算法


Sort* AFLSort = NULL; //

//function---------------------------------------------------------------------------
u8 initSort(u8 sort_id) {
	switch (sort_id) {
	//0
	case NO_SORT_0: {
		AFLSort = new No_Sort();
		break;	}
	case Random_Sort_1: {
		AFLSort = new  Random_Sort();
		break;	}
	case BT_dup_Sort_2: {
		AFLSort = new BT_dup_Sort();
		break;	}
	case BT_no_dup_Sort_3: {
		AFLSort = new BT_no_dup_Sort();
		break;	}
	case BA_Sort_4: {
		AFLSort = new BA_Sort();
		break;	}
	case MIn_Max_Sort_5: {
		AFLSort = new MIn_Max_Sort();
		break;	}
	case Short_first_Sort_6: {
		AFLSort = new Short_first_Sort();
		break;	}
	case Short_by_hamming_7: {
			AFLSort = new Short_by_hamming();
			break;	}

	default:
		break;
	}

	return 1;
}

void on_new_seed_generated(struct queue_entry *queue,struct queue_entry *q)//q1 是最新的
{
struct queue_entry *queue_cur = queue;
	double distance=0;
	while (queue_cur)
	{
		if ( queue_cur==q)
		{
			break;// the last is the self
		}
		distance=cal_two_input(queue_cur,q);//左边为旧,小号;右边是新,大号
		//生成一调新的记录
		DP tmp;
		tmp.distance=distance;
		tmp.fname_min=queue_cur->fname;
		tmp.fname_max=q->fname;
		dis_list.insert(tmp); //插入之后是有序的
		queue_cur = queue_cur->next;
	}
	//输出总的记录
	update_sort_file();
}


void update_sort_file()
{
	//n个测试用例,就有n(n-1)/2次比较
		//输出文件定义
		fseek(distance_file,0,0);
		set<u8*>cached_list;
		// 遍历 set
		for (auto it = dis_list.begin(), end = dis_list.end(); it != end; it++)
		{
			DP tmp = *it; //按照distance下的顺序进行
			if (!cached_list.empty())
			{
				if (cached_list.find(tmp.fname_min) != cached_list.end() and cached_list.find(tmp.fname_max) != cached_list.end())
				{
					continue;
				}
			}
			if (tmp.fmax_bitmap_size>tmp.fmin_bitmap_size  ) //max 表示id大的,即是新的,但是新的也不一定好
			{
				fprintf(distance_file, "%s; %s; %0.f \n", "", tmp.fname_max, tmp.distance);
			}
			else
			{
				fprintf(distance_file, "%s; %s; %0.f \n", tmp.fname_min, "", tmp.distance);
			}

			fflush(distance_file);
			cached_list.insert(tmp.fname_min);
			cached_list.insert(tmp.fname_max);
		}


}




void sort_distance() {
	//sort the vector of the distance of between all the inputs
}

