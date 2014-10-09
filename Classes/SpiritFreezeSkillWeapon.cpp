#include "SpiritFreezeSkillWeapon.h"
#include "EntityManager.h"
#include "TimeTool.h"

SpiritFreezeSkillWeapon::SpiritFreezeSkillWeapon( GameCharacter* owner ):Weapon(owner, SPIRIT_FREEZE_SKILL_WEAPON)
    , m_actionName("atk3"), m_attRadius(600)
{
    m_minAttackInterval     =   4;
}

SpiritFreezeSkillWeapon::~SpiritFreezeSkillWeapon()
{

}

void SpiritFreezeSkillWeapon::attack( GameCharacter* target )
{
    // ����ʱҲ��Ҫ���Ŷ���
    m_pOwner->getShape()->playAction(m_actionName, false,
        std::bind(&SpiritFreezeSkillWeapon::onAttackEffect, this, std::placeholders::_1));

    // ��¼һ�µ�ǰ��ʱ��
    m_lastAttackTime        =   TimeTool::getSecondTime();
    m_nextAttackReadyTime   =   m_lastAttackTime + m_minAttackInterval;
    m_targetId              =   target->getId();
}

bool SpiritFreezeSkillWeapon::isInAttackRange( GameCharacter* target )
{
    auto tmpOwnerPos    =   m_pOwner->getMovingEntity().getPosition();
    auto tmpTargetPos   =   target->getMovingEntity().getPosition();
    return (tmpOwnerPos - tmpTargetPos).getLengthSq() <= m_attRadius * m_attRadius;
}

bool SpiritFreezeSkillWeapon::isReadyForNextAttack()
{
    return m_nextAttackReadyTime < TimeTool::getSecondTime();
}

bool SpiritFreezeSkillWeapon::isAttacking()
{
    return m_pOwner->getShape()->getCurrentAnimationName() == m_actionName;
}

void SpiritFreezeSkillWeapon::onAttackEffect( string evt )
{
    if (!isTargetAlive())
    {
        return;
    }

    /**
    *	 @_@ ���𹥻�����ʵ�����õ��˽��붳��״̬����ʾ��һ����ʱҲ����
    *   ״̬���棬�Ժ���ܻ���ʹ����Ϣ�ķ�ʽ������Ŀǰͼ�򵥣���ֱ���޸�
    *   Ŀ���״̬
    */
    auto tmpTarget  =   
        dynamic_cast<GameCharacter*>(EntityMgr->getEntityFromID(m_targetId));
    tmpTarget->getFSM()->changeState(GameCharacterFrozenState::create());

    // @_@ Ӧ�û�������˺���������ʱ���Ų�д
}

bool SpiritFreezeSkillWeapon::isTargetAlive()
{
    auto tmpCharacter   =   dynamic_cast<GameCharacter*>(EntityMgr->getEntityFromID(m_targetId));
    return tmpCharacter != nullptr && tmpCharacter->isAlive();
}