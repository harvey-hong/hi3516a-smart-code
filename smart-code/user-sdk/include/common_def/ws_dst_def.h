#ifndef _WS_DST_DEF_H_
#define _WS_DST_DEF_H_

#include "ws_comm_type.h"

#ifdef __cplusplus
extern "C" {
namespace ws_soft
{
#endif

#define WS_DST_LAST_WEEK 100                //��ʾ���һ������

#define WS_DST_ENTER_FILE           "/config/dst_enter.dat"
#define WS_DST_OUT_FILE               "/config/dst_out.dat"

#define WS_DST_TIME_FLAG              "/config/dst_time_FLAG"          

typedef enum
{
    TIME_ZONE_WEST_LINE = 0,                            //�ս�����
    TIME_ZONE_SAMOA,                                            //��Ħ��Ⱥ��
    TIME_ZONE_COORDINATED_11,                           //Э������ʱ-11
    TIME_ZONE_HAWAII,                                           //������
    TIME_ZONE_ALASKA,                                           //����˹��
    TIME_ZONE_PACIFIC_OCEAN,                            //̫ƽ��ʱ��(�����ͼ��ô�)
    TIME_ZONE_CALIFORNIA,                                   //�¼�����������
    TIME_ZONE_CHIHUAHUA_OLD,                            //�����ߣ�����˹����������(��)
    TIME_ZONE_CHIHUAHUA_NEW,                            //�����ߣ�����˹����������(��)
    TIME_ZONE_MOUNTAIN,                                     //ɽ��ʱ��(�����ͼ��ô�)
    TIME_ZONE_ARIZONA,                                      //����ɣ��
    TIME_ZONE_GUADALAJARA_OLD,                      //�ϴ���������ī����ǣ�������(��)
    TIME_ZONE_GUADALAJARA_NEW,                      //�ϴ���������ī����ǣ�������(��)
    TIME_ZONE_SASS,                         //��˹�Ƴ���
    TIME_ZONE_CENTRAL_CANADA,               //�в�ʱ��(�����ͼ��ô�)
    TIME_ZONE_CENTRAL_AMERICA,              //������
    TIME_ZONE_BOGOTA,                     //�������������
    TIME_ZONE_EASTERN_TIME_CANADA,        //����ʱ��(�����ͼ��ô�)
    TIME_ZONE_INDIANA,                    //ӡ�ڰ�����(����)
    TIME_ZONE_CARACAS,                    //������˹
    TIME_ZONE_ATLANTIC_CANADA,            //������ʱ��(���ô�)
    TIME_ZONE_CUIABA,                     //���ǰ�
    TIME_ZONE_GEORGETOWN,                 //���ζأ�����˹�����˹��ʥ����
    TIME_ZONE_SANTIAGO,                   //ʥ���Ǹ�
    TIME_ZONE_ASUNCION,                   //����ɭ
    TIME_ZONE_NEWFOUNDLAND,               //Ŧ����
    TIME_ZONE_BRASILIA,                   //��������
    TIME_ZONE_BUENOS_AIRES,               //����ŵ˹����˹
    TIME_ZONE_GREENLAND,                  //������
    TIME_ZONE_CAYENNE,                    //���磬��������
    TIME_ZONE_MONTEVIDEO,                 //�ɵ�ά����
    TIME_ZONE_SALVADOR,                   //�����߶�
    TIME_ZONE_COORDINATED_2,              //Э������ʱ-02
    TIME_ZONE_ATLANTIC_OCEAN,             //�д�����
    TIME_ZONE_ANGLE_ISLANDS,              //���½�Ⱥ��
    TIME_ZONE_AZORES_ISLANDS,             //���ٶ�Ⱥ��
    TIME_ZONE_GREENWICH,                  //�������α�׼ʱ�䣺�����֣����������׶أ���˹��
    TIME_ZONE_CASABLANK,                  //��ɯ������
    TIME_ZONE_MONROVIA,                   //����ά�ǣ��׿���δ��
    TIME_ZONE_CORRDINATED,                //Э������ʱ
    TIME_ZONE_AMSTERDAM,                  //��ķ˹�ص������֣������ᣬ����˹�¸��Ħ��άҲ��
    TIME_ZONE_BELGRADE,                   //���������£�������˹������������˹��¬��������
    TIME_ZONE_BRUSSELS,                   //��³�������籾��������������
    TIME_ZONE_SARAJEVO,                   //�������ѣ�˹�������ɳ�������ղ�
    TIME_ZONE_WESTERN_CENTRAL_AFRICA,     //�з�����
    TIME_ZONE_WINDHOEK,                   //�µúͿ�
    TIME_ZONE_AMMAN,                      //����
    TIME_ZONE_BEIRUT,                     //��³��
    TIME_ZONE_DAMASCUS,                   //����ʿ��
    TIME_ZONE_HRE,                        //�����ף�����������
    TIME_ZONE_HELSINKI,                   //�ն���������������ӣ������ǣ����֣�ά��Ŧ˹
    TIME_ZONE_CAIRO,                      //����
    TIME_ZONE_NICOSIA,                    //�������
    TIME_ZONE_ATHENS,                     //�ŵ䣬������˹��
    TIME_ZONE_JERUSALEM,                  //Ү·����
    TIME_ZONE_ISTANBUL,                   //��˹̹����
    TIME_ZONE_KALININGRAD,                //���������գ���˹��
    TIME_ZONE_BAGHDAD,                    //�͸��
    TIME_ZONE_KUWAIT,                     //�����أ����ŵ�
    TIME_ZONE_NAIROBI,                    //���ޱ�
    TIME_ZONE_MOSCOW,                     //Ī˹�ƣ�ʥ�˵ñ��������Ӹ���
    TIME_ZONE_TEHERAN,                    //�º���
    TIME_ZONE_ABU_DHABI,                  //�������ȣ���˹����
    TIME_ZONE_YEREVAN,                    //������
    TIME_ZONE_BAKU,                       //�Ϳ�
    TIME_ZONE_TBILISI,                    //�ڱ���˹
    TIME_ZONE_CAUCASUS,                   //�߼�����׼ʱ��
    TIME_ZONE_PORT_LOUIS,                 //·�׸�
    TIME_ZONE_KABUL,                      //������
    TIME_ZONE_TASHKENT,                   //��ʲ��
    TIME_ZONE_ISB,                        //��˹������������
    TIME_ZONE_EKATERINBURG,               //Ҷ�����ձ�
    TIME_ZONE_MADRAS,                     //�����˹���Ӷ����������µ���
    TIME_ZONE_SRIWALDEN,                  //˹����ǻ���������
    TIME_ZONE_KATHMANDU,                  //�ӵ�����
    TIME_ZONE_ASTANA,                     //��˹����
    TIME_ZONE_DACCA,                      //�￨
    TIME_ZONE_NOVOSIBIRSK,                //����������
    TIME_ZONE_RANGOON,                    //����
    TIME_ZONE_BANGKOK,                    //���ȣ����ڣ��żӴ�
    TIME_ZONE_KRASNOYARSK,                //����˹ŵ�Ƕ�˹��
    TIME_ZONE_BEIJING,                    //���������죬����ر�����������³ľ��
    TIME_ZONE_KUALA_LUMPUR,               //��¡�£��¼���
    TIME_ZONE_PERTH,                      //��˹
    TIME_ZONE_TAIPEI,                     //̨��
    TIME_ZONE_ULAN_BATOR,                 //��������
    TIME_ZONE_IKT,                        //������Ŀ�
    TIME_ZONE_OSAKA,                      //���棬���ϣ�����
    TIME_ZONE_SEOUL,                      //����
    TIME_ZONE_YAKUTSK,                    //�ſ�Ŀ�
    TIME_ZONE_ADELAIDE,                   //��������
    TIME_ZONE_DARWIN,                     //�����
    TIME_ZONE_BNE,                        //����˹��
    TIME_ZONE_GUAM,                       //�ص���Ī���ȱȸ�
    TIME_ZONE_HOBART,                     //������
    TIME_ZONE_CANBERRA,                   //��������ī������Ϥ��
    TIME_ZONE_VVO,                        //��������˹�п�
    TIME_ZONE_SOLOMON_ISLANDS,            //������Ⱥ�����¿��������
    TIME_ZONE_MAGADAN,                    //��ӵ�
    TIME_ZONE_OSKLAND,                    //�¿��������ֶ�
    TIME_ZONE_SKIN_DROGBA,                //Ƥ���ް͸����˹��-����� - ����
    TIME_ZONE_FIJI ,                      //쳼�
    TIME_ZONE_COORDINATED_12,             //Э������ʱ+12
    TIME_ZONE_NUKUALOFA,                  //Ŭ�Ⱒ�巨


} time_zone_type;

typedef struct
{
    WS_U16 month;
    WS_U16 wday_idx;        //�ڼ�������
    WS_U16 wday;            //���ڼ�
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
    ENTER_DST,          //����DSTʱ��
    OUT_OF_DST,         //��DSTʱ��
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

