#ifndef __PROJECTILE_H__
#define __PROJECTILE_H__

#include "cocos2d.h"
#include "GameCharacter.h"

using namespace cocos2d;

/**
*	 ���ӵ����͡�����Ҫ��ϣ����ͨ��Զ�������벻ͬ�ġ��ӵ�������������
*   ��ɫ�Ĳ�ͬ��ͨԶ�̹�����ʽ
*/
enum ProjectileTypeEnum
{
    PROJECTILE_TYPE_GALAXO_BALL,                // ������
};

/**
*	���ӵ�״̬���ı�־λ����ȫΪ0��ʱ���ֱ��ɾ��
*/
enum ProjectileStateEnum
{
    PROJECTILE_STATE_UPDATEMOVEMENT =   0x00001,        // �ӵ������ƶ��ĸ���
    PROJECTILE_STATE_UPDATE         =   0x00002,        // ����λ������ĸ���
};

/**
*	 Զ�̹������������ġ��ӵ���
*/
class Projectile : public Ref
{
public:
    /**
    *	ֻ��ͨ������ӿڴ����ӵ���������Ϊ���ƹ��������ã������ṩһ������
    *   �Զ������ݵ���������create��Ӧ�����������ݲ�ͬ������ʹ���������
    */
    static Projectile* create(GameCharacterAttribute& att, ProjectileTypeEnum type, void* extraData);

    /**
    *	�����ӵ��ĳ�ʼ�����������ݳ�ʼ��������ʼ�ٶ�
    */
    void setOrientation(Vec2 orientation);

    /**
    *	������ʾ�ڵ㣬������������ͼ����ʾ�б� 
    */
    virtual Node* getShape() = 0;

    /**
    *	�ڴ˴���ɳ���λ�Ƹ����������������
    */
    virtual void update(float dm) = 0;

    /**
    *	�ڴ˴����λ�Ƹ��� 
    */
    virtual void updateMovement(float dm) = 0;

protected:
    /**
    *	�ӵ������λ�ú��ٶȻ��о��Ƿ����ߵ�����һ����棬��ײ���������������Ա仯��
    *   �ӵ��������뷢�����޹���
    */
    Projectile(GameCharacterAttribute& att);

    virtual ~Projectile() {}

    /**
    *	����λ�Ƶģ����ӵ������ú���Ҫ
    */
    CC_SYNTHESIZE(Vec2, m_position, Position);                 // ����
    Vec2    m_velocity;                                        // �ٶ�ʸ��
    float   m_rate;                                            // �ٶȱ���

    /**
    *	�����ӵ���״̬ 
    */
    CC_SYNTHESIZE(int, m_state, State);

    bool canUpdate() { return (m_state & PROJECTILE_STATE_UPDATE) != 0; }
    bool canUpdateMovement() { return (m_state & PROJECTILE_STATE_UPDATEMOVEMENT) != 0; }
    bool canRemove() { return m_state == 0; }
    void updateOff() { m_state &= ~PROJECTILE_STATE_UPDATE; }
    void updateMovementOff() { m_state &= ~PROJECTILE_STATE_UPDATEMOVEMENT; }

    /**
    *	�������ڼ���ķ����ߵĸ������� 
    */
    GameCharacterAttribute      m_senderAtt;

private:
    ProjectileTypeEnum          m_projectileType;               // ���ӵ�������
    static int m_count;
    CC_SYNTHESIZE_READONLY(int, m_projectileId, ProjectileId);  // Ψһ��ʶ
};

#endif