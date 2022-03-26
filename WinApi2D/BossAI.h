#pragma once


class CBState;
class CFennel;

class BossAI 
{
		friend class CFennel;

	private:
		map<Boss_Pattern, CBState*> m_mapState;
		CFennel* m_pOwner;
		CBState* m_pCurState;

	public:
		BossAI();
		~BossAI();

		CFennel* GetOwnerAI();

		CBState* GetState(Boss_Pattern state);
		void SetCurState(Boss_Pattern state);

		void update();

		void AddState(CBState* state);
		void ChangeState(Boss_Pattern nextState);
};

