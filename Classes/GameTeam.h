#ifndef __GAME_TEAM_H__
#define __GAME_TEAM_H__

#include "cocos2d.h"
#include "Telegram.h"
#include "BaseGameEntity.h"
#include "Formation.h"

using namespace cocos2d;
using namespace std;

class GameCharacter;

/**
	 游戏中我方队伍的概念，为了实现队伍级别的组合、AI的概念
     @_@    这里就不考虑敌方队伍这个概念
*/
class GameTeam : public Ref
{
public:
    ~GameTeam();

    /**
    	 给该队伍添加成员，同时指定该角色在阵型中的位置编号
    */
    void addMember(GameCharacter* player, int posId = 0);

    /**
    	 每一帧中回调，在这里会调用所有成员的update
    */
    void update(float dm);

    // 返回队伍阵型
    Formation& getTeamFormation() { return m_formation; }

    // 队伍id，用来全局唯一标示一个队伍
    CC_SYNTHESIZE(int, m_teamId, TeamId);

    // 创建一个队伍，在调用这个函数后该队伍就被加入到TeamMgr中了
    static GameTeam* create();

private:
    GameTeam();

    // 删除处于死亡状态的角色
    void removeDeadCharacter();

    static int m_nextValidId;                                   // 下一个有效地队伍id

    list<GameCharacter*>        m_members;                      // 队伍的所有成员

    Formation                   m_formation;                    // 阵型
};

#endif