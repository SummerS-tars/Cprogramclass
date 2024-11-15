#include <stdio.h>

extern struct playerInfo
{
    int px , py ;               // 位置信息
    int energyCost ;            // 体力消耗
    int getTreasure ;           // 获得宝物数量
    int getTrap ;               // 是否触发陷阱
};

extern moveJudge( struct playerInfo *player )
{
    
}

extern moveAction( struct playerInfo *player , int direction )
{
    switch( direction )
    {
        case 'w' : player->py ++ ; break ;
        case 's' : player->py -- ; break ;
        case 'a' : player->px -- ; break ;
        case 'd' : player->px ++ ; break ;
        default : break ;
    }
}