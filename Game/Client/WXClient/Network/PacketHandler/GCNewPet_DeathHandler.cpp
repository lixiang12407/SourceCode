#include "StdAfx.h"
#include "..\..\NetWork\NetManager.h"
#include "TDTimeSystem.h"
#include "TDException.h"
#include "CGCharAskBaseAttrib.h"
#include "..\..\GameCommand.h"
#include "..\..\Procedure\GameProcedure.h"
#include "..\..\Object\ObjectManager.h"
#include "..\..\Object\Character\Obj_PlayerNPC.h"
#include "..\..\Object\ObjectCommandDef.h"
#include "..\..\Interface\GMGameInterface.h"
#include "..\..\World\WorldManager.h"
#include "..\..\DataPool\GMDP_CharacterData.h"

#include "GCNewPet_Death.h"
#include "..\..\Object\GMObjectLoadQueue.h"
#include "..\WxRender\RenderSystem.h"

uint GCNewPet_DeathHandler::Execute( GCNewPet_Death* pPacket, Player* pPlayer ) 
{
	//��ǰ������������
	if(CGameProcedure::GetActiveProcedure() == (CGameProcedure*)CGameProcedure::s_pProcMain)
	{
		CObjectManager* pObjectManager = CObjectManager::GetMe();
		//���λ���Ƿ�Ϸ�
		if(!CWorldManager::GetMe()->GetActiveScene()->IsValidPosition(fVector2(pPacket->getWorldPos().m_fX, pPacket->getWorldPos().m_fZ)))
		{
			TDThrow("ERROR POSITION @ GCNewMonster_DeathHandler");
		}

		//�������
		CObject_PlayerNPC* pNPC = (CObject_PlayerNPC*)pObjectManager->FindServerObject( (INT)pPacket->getObjID() );
		fVector3 fvGame;
		CGameProcedure::s_pGfxSystem->Axis_Trans(
			CRenderSystem::AX_PLAN, fVector3(pPacket->getWorldPos().m_fX, 0.0f, pPacket->getWorldPos().m_fZ),
			CRenderSystem::AX_GAME, fvGame);

		FLOAT fFaceDir = pPacket->getDir();
		if ( pNPC == NULL )
		{
			pNPC = pObjectManager->NewPlayerNPC( (INT)pPacket->getObjID() );

			SObjectInit initPlayerNPC;

			initPlayerNPC.m_fvPos = fvGame;
			initPlayerNPC.m_fvRot = fVector3( 0.f, fFaceDir, 0.f );

			pNPC->Initial( &initPlayerNPC );
		}
		else
		{
			fVector2 mapPos(fvGame.x, fvGame.z);
			pNPC->SetMapPosition(mapPos);
			pNPC->SetFaceDir( fFaceDir );
			pNPC->Enable( OSF_VISIABLE );
			pNPC->Disalbe( OSF_OUT_VISUAL_FIELD );
		}
		pNPC->SetNpcType(NPC_TYPE_PET);

		pNPC->GetCharacterData()->Set_MoveSpeed(pPacket->getMoveSpeed());

		SCommand_Object cmdTemp;
		cmdTemp.m_wID			= OC_DEATH;
		cmdTemp.m_abParam[0]	= FALSE;
		pNPC->PushCommand(&cmdTemp );

		//�������ѡ��NPC
		if (CObjectManager::GetMe()->GetMainTarget() && pNPC &&
			((CObject*)(CObjectManager::GetMe()->GetMainTarget()))->GetID() == pNPC->GetID())
		{
			CGameInterface::GetMe()->Object_SelectAsMainTarget(INVALID_ID);
		}

		//����Ask����
		CObjectManager::GetMe()->GetLoadQueue()->TryAddLoadTask(pNPC->GetID(), CObject_Character::CT_MONSTER);

		// tempcode{
		// �˰治����������æ�ͻ����Ӻ���Ϣ�Ĵ���
//		CGCharAskBaseAttrib msgAskBaseAttrib;
//		msgAskBaseAttrib.setTargetID( (INT)pPacket->getObjID() );
//		CNetManager::GetMe()->SendPacket( &msgAskBaseAttrib );
		// }

		//ͬ����Ⱦ��
		char szTemp[MAX_PATH];
		_snprintf(szTemp, MAX_PATH, "GCNewPet_Death(%.1f,%.1f)", 
			pPacket->getWorldPos().m_fX, pPacket->getWorldPos().m_fZ);
		pNPC->PushDebugString(szTemp);
		pNPC->SetMsgTime(CGameProcedure::s_pTimeSystem->GetTimeNow());
	}

	return PACKET_EXE_CONTINUE ;
}