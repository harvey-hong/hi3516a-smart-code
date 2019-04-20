#ifndef _WS_DST_DEF_H_
#define _WS_DST_DEF_H_

#include "ws_comm_type.h"

#ifdef __cplusplus
extern "C" {
namespace ws_soft
{
#endif

#define WS_DST_LAST_WEEK 100                //表示最后一个星期

#define WS_DST_ENTER_FILE           "/config/dst_enter.dat"
#define WS_DST_OUT_FILE               "/config/dst_out.dat"

#define WS_DST_TIME_FLAG              "/config/dst_time_FLAG"          

typedef enum
{
    TIME_ZONE_WEST_LINE = 0,                            //日界线西
    TIME_ZONE_SAMOA,                                            //萨摩亚群岛
    TIME_ZONE_COORDINATED_11,                           //协调世界时-11
    TIME_ZONE_HAWAII,                                           //夏威夷
    TIME_ZONE_ALASKA,                                           //阿拉斯加
    TIME_ZONE_PACIFIC_OCEAN,                            //太平洋时间(美国和加拿大)
    TIME_ZONE_CALIFORNIA,                                   //下加利福利亚洲
    TIME_ZONE_CHIHUAHUA_OLD,                            //奇瓦瓦，拉巴斯，马萨特兰(旧)
    TIME_ZONE_CHIHUAHUA_NEW,                            //奇瓦瓦，拉巴斯，马萨特兰(新)
    TIME_ZONE_MOUNTAIN,                                     //山地时间(美国和加拿大)
    TIME_ZONE_ARIZONA,                                      //亚利桑那
    TIME_ZONE_GUADALAJARA_OLD,                      //瓜达拉哈拉，墨西哥城，蒙特雷(旧)
    TIME_ZONE_GUADALAJARA_NEW,                      //瓜达拉哈拉，墨西哥城，蒙特雷(新)
    TIME_ZONE_SASS,                         //萨斯科彻温
    TIME_ZONE_CENTRAL_CANADA,               //中部时间(美国和加拿大)
    TIME_ZONE_CENTRAL_AMERICA,              //中美洲
    TIME_ZONE_BOGOTA,                     //波哥大，利马，基多
    TIME_ZONE_EASTERN_TIME_CANADA,        //东部时间(美国和加拿大)
    TIME_ZONE_INDIANA,                    //印第安纳州(东部)
    TIME_ZONE_CARACAS,                    //加拉加斯
    TIME_ZONE_ATLANTIC_CANADA,            //大西洋时间(加拿大)
    TIME_ZONE_CUIABA,                     //库亚巴
    TIME_ZONE_GEORGETOWN,                 //乔治敦，拉巴斯，马瑙斯，圣胡安
    TIME_ZONE_SANTIAGO,                   //圣地亚哥
    TIME_ZONE_ASUNCION,                   //亚松森
    TIME_ZONE_NEWFOUNDLAND,               //纽芬兰
    TIME_ZONE_BRASILIA,                   //巴西利亚
    TIME_ZONE_BUENOS_AIRES,               //布宜诺斯艾利斯
    TIME_ZONE_GREENLAND,                  //格陵兰
    TIME_ZONE_CAYENNE,                    //卡宴，福特雷萨
    TIME_ZONE_MONTEVIDEO,                 //蒙得维的亚
    TIME_ZONE_SALVADOR,                   //萨尔瓦多
    TIME_ZONE_COORDINATED_2,              //协调世界时-02
    TIME_ZONE_ATLANTIC_OCEAN,             //中大西洋
    TIME_ZONE_ANGLE_ISLANDS,              //福德角群岛
    TIME_ZONE_AZORES_ISLANDS,             //亚速尔群岛
    TIME_ZONE_GREENWICH,                  //格林威治标准时间：都柏林，爱丁堡，伦敦，里斯本
    TIME_ZONE_CASABLANK,                  //卡莎布兰卡
    TIME_ZONE_MONROVIA,                   //蒙罗维亚，雷克雅未克
    TIME_ZONE_CORRDINATED,                //协调世界时
    TIME_ZONE_AMSTERDAM,                  //阿姆斯特丹，柏林，伯尔尼，罗马，斯德哥尔摩，维也纳
    TIME_ZONE_BELGRADE,                   //贝尔格莱德，布拉迪斯拉发，布达佩斯，卢布尔雅那
    TIME_ZONE_BRUSSELS,                   //布鲁塞尔，哥本哈根，马德里，巴黎
    TIME_ZONE_SARAJEVO,                   //萨拉热窝，斯科普里，华沙，萨格勒布
    TIME_ZONE_WESTERN_CENTRAL_AFRICA,     //中非西部
    TIME_ZONE_WINDHOEK,                   //温得和克
    TIME_ZONE_AMMAN,                      //安曼
    TIME_ZONE_BEIRUT,                     //贝鲁特
    TIME_ZONE_DAMASCUS,                   //大马士革
    TIME_ZONE_HRE,                        //哈拉雷，比勒陀利亚
    TIME_ZONE_HELSINKI,                   //赫尔辛基，基辅，里加，索菲亚，塔林，维尔纽斯
    TIME_ZONE_CAIRO,                      //开罗
    TIME_ZONE_NICOSIA,                    //尼科西亚
    TIME_ZONE_ATHENS,                     //雅典，布加勒斯特
    TIME_ZONE_JERUSALEM,                  //耶路撒冷
    TIME_ZONE_ISTANBUL,                   //伊斯坦布尔
    TIME_ZONE_KALININGRAD,                //加里宁格勒，明斯克
    TIME_ZONE_BAGHDAD,                    //巴格达
    TIME_ZONE_KUWAIT,                     //科威特，利雅得
    TIME_ZONE_NAIROBI,                    //内罗毕
    TIME_ZONE_MOSCOW,                     //莫斯科，圣彼得堡，伏尔加格勒
    TIME_ZONE_TEHERAN,                    //德黑兰
    TIME_ZONE_ABU_DHABI,                  //阿布扎比，马斯喀特
    TIME_ZONE_YEREVAN,                    //埃里温
    TIME_ZONE_BAKU,                       //巴库
    TIME_ZONE_TBILISI,                    //第比利斯
    TIME_ZONE_CAUCASUS,                   //高加索标准时间
    TIME_ZONE_PORT_LOUIS,                 //路易港
    TIME_ZONE_KABUL,                      //喀布尔
    TIME_ZONE_TASHKENT,                   //塔什干
    TIME_ZONE_ISB,                        //伊斯兰堡，卡拉奇
    TIME_ZONE_EKATERINBURG,               //叶卡捷琳堡
    TIME_ZONE_MADRAS,                     //马德拉斯，加尔各答，孟买，新德里
    TIME_ZONE_SRIWALDEN,                  //斯里哈亚华登尼普拉
    TIME_ZONE_KATHMANDU,                  //加德满都
    TIME_ZONE_ASTANA,                     //阿斯塔纳
    TIME_ZONE_DACCA,                      //达卡
    TIME_ZONE_NOVOSIBIRSK,                //新西伯利亚
    TIME_ZONE_RANGOON,                    //仰光
    TIME_ZONE_BANGKOK,                    //曼谷，河内，雅加达
    TIME_ZONE_KRASNOYARSK,                //克拉斯诺亚尔斯克
    TIME_ZONE_BEIJING,                    //北京，重庆，香港特别行政区，乌鲁木齐
    TIME_ZONE_KUALA_LUMPUR,               //吉隆坡，新加坡
    TIME_ZONE_PERTH,                      //珀斯
    TIME_ZONE_TAIPEI,                     //台北
    TIME_ZONE_ULAN_BATOR,                 //乌兰巴托
    TIME_ZONE_IKT,                        //伊尔库茨克
    TIME_ZONE_OSAKA,                      //大阪，札幌，东京
    TIME_ZONE_SEOUL,                      //汉城
    TIME_ZONE_YAKUTSK,                    //雅库茨克
    TIME_ZONE_ADELAIDE,                   //阿德莱德
    TIME_ZONE_DARWIN,                     //达尔文
    TIME_ZONE_BNE,                        //布里斯班
    TIME_ZONE_GUAM,                       //关岛，莫尔兹比港
    TIME_ZONE_HOBART,                     //霍巴特
    TIME_ZONE_CANBERRA,                   //堪培拉，墨尔本，悉尼
    TIME_ZONE_VVO,                        //符拉迪沃斯托克
    TIME_ZONE_SOLOMON_ISLANDS,            //所罗门群岛，新喀里多尼亚
    TIME_ZONE_MAGADAN,                    //马加丹
    TIME_ZONE_OSKLAND,                    //奥克兰，惠林顿
    TIME_ZONE_SKIN_DROGBA,                //皮德罗巴甫洛夫斯基-勘察加 - 旧用
    TIME_ZONE_FIJI ,                      //斐济
    TIME_ZONE_COORDINATED_12,             //协调世界时+12
    TIME_ZONE_NUKUALOFA,                  //努库阿洛法


} time_zone_type;

typedef struct
{
    WS_U16 month;
    WS_U16 wday_idx;        //第几个星期
    WS_U16 wday;            //星期几
    WS_U16 hour;
    WS_U16 min;
    WS_U16 day;     
} time_dst;

typedef struct
{
    time_zone_type zone_type;
    WS_BOOL is_have_dst;
    time_dst start_dst;
    time_dst end_dst;
    int zone_hour;
    int zone_min;
} dst_ctr;

typedef struct
{
    int support_num;
    dst_ctr *zone;
} ws_support_time_zone;

typedef enum
{
    NO_IN_DST = 0,
    ENTER_DST,          //进入DST时区
    OUT_OF_DST,         //出DST时区
} ws_dst_type;

typedef enum
{
    CHANGE_AS_DAY,
    CHANGE_AS_WEEKEND,
}dst_model;

typedef struct
{
    WS_BOOL enable_dst;
    dst_model model;
    WS_U16 time_difference;
    time_dst dst_start_time;
    time_dst dst_end_time;
}dst_setting;

#ifdef __cplusplus
}//namespace ws_soft {
}//extern "C" {
#endif

#endif  //_WS_DST_DEF_H_

