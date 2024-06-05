#include "base/atRTTI.hpp"
#include "base/CBaseModelInfo.hpp"
#include "base/CNavigation.hpp"
#include "base/CObject.hpp"
#include "base/datBase.hpp"
#include "base/fwArchetype.hpp"
#include "base/fwArchetypeDef.hpp"
#include "base/fwExtensibleBase.hpp"
#include "base/fwExtension.hpp"
#include "base/fwExtensionContainer.hpp"
#include "base/fwRefAwareBase.hpp"
#include "base/fwRefAwareBaseImpl.hpp"
#include "base/HashTable.hpp"
#include "base/pgBase.hpp"
#include "base/phArchetype.hpp"
#include "base/phBound.hpp"
#include "base/phBoundCapsule.hpp"
#include "base/phBoundComposite.hpp"
#include "base/pgDictionary.hpp"
#include "camera/CCameraAngles.hpp"
#include "camera/CCameraManagerAngles.hpp"
#include "camera/CGameCameraAngles.hpp"
#include "draw_handlers/CEntityDrawHandler.hpp"
#include "draw_handlers/CObjectDrawHandler.hpp"
#include "draw_handlers/CPedDrawHandler.hpp"
#include "draw_handlers/CVehicleDrawHandler.hpp"
#include "draw_handlers/fwDrawData.hpp"
#include "entities/CAttackers.hpp"
#include "entities/CDynamicEntity.hpp"
#include "entities/CEntity.hpp"
#include "entities/CPhysical.hpp"
#include "entities/fwEntity.hpp"
#include "enums/eExplosionTag.hpp"
#include "enums/eHandlingType.hpp"
#include "game_files/CGameConfig.hpp"
#include "game_files/GameDataHash.hpp"
#include "misc/CTunables.hpp"
#include "misc/vfx/TimecycleKeyframeData.hpp"
#include "netsync/CProjectBaseSyncDataNode.hpp"
#include "netsync/CProjectSyncTree.hpp"
#include "netsync/netSyncDataNode.hpp"
#include "netsync/netSyncNodeBase.hpp"
#include "netsync/netSyncParentNode.hpp"
#include "netsync/netSyncTree.hpp"
#include "netsync/NodeCommonDataOperations.hpp"
#include "netsync/nodes/automobile/CAutomobileCreationNode.hpp"
#include "netsync/nodes/CPedComponents.hpp"
#include "netsync/nodes/door/CDoorCreationDataNode.hpp"
#include "netsync/nodes/door/CDoorMovementDataNode.hpp"
#include "netsync/nodes/door/CDoorScriptGameStateDataNode.hpp"
#include "netsync/nodes/door/CDoorScriptInfoDataNode.hpp"
#include "netsync/nodes/dynamic_entity/CDynamicEntityGameStateDataNode.hpp"
#include "netsync/nodes/entity/CEntityOrientationDataNode.hpp"
#include "netsync/nodes/entity/CEntityScriptGameStateDataNode.hpp"
#include "netsync/nodes/entity/CEntityScriptInfoDataNode.hpp"
#include "netsync/nodes/heli/CHeliHealthDataNode.hpp"
#include "netsync/nodes/heli/CHeliControlDataNode.hpp"
#include "netsync/nodes/object/CObjectCreationDataNode.hpp"
#include "netsync/nodes/ped/CPedAIDataNode.hpp"
#include "netsync/nodes/ped/CPedAppearanceDataNode.hpp"
#include "netsync/nodes/ped/CPedAttachDataNode.hpp"
#include "netsync/nodes/ped/CPedComponentReservationDataNode.hpp"
#include "netsync/nodes/ped/CPedCreationDataNode.hpp"
#include "netsync/nodes/ped/CPedGameStateDataNode.hpp"
#include "netsync/nodes/ped/CPedHealthDataNode.hpp"
#include "netsync/nodes/ped/CPedInventoryDataNode.hpp"
#include "netsync/nodes/ped/CPedMovementDataNode.hpp"
#include "netsync/nodes/ped/CPedMovementGroupDataNode.hpp"
#include "netsync/nodes/ped/CPedOrientationDataNode.hpp"
#include "netsync/nodes/ped/CPedScriptCreationDataNode.hpp"
#include "netsync/nodes/ped/CPedTaskSequenceDataNode.hpp"
#include "netsync/nodes/ped/CPedTaskSpecificDataNode.hpp"
#include "netsync/nodes/ped/CPedTaskTreeDataNode.hpp"
#include "netsync/nodes/physical/CPhysicalAngVelocityDataNode.hpp"
#include "netsync/nodes/physical/CPhysicalAttachDataNode.hpp"
#include "netsync/nodes/physical/CPhysicalGameStateDataNode.hpp"
#include "netsync/nodes/physical/CPhysicalHealthDataNode.hpp"
#include "netsync/nodes/physical/CPhysicalMigrationDataNode.hpp"
#include "netsync/nodes/physical/CPhysicalScriptGameStateDataNode.hpp"
#include "netsync/nodes/physical/CPhysicalScriptMigrationDataNode.hpp"
#include "netsync/nodes/physical/CPhysicalVelocityDataNode.hpp"
#include "netsync/nodes/pickup/CPickupCreationDataNode.hpp"
#include "netsync/nodes/pickup_placement/CPickupPlacementCreationDataNode.hpp"
#include "netsync/nodes/player/CPlayerAmbientModelStreamingNode.hpp"
#include "netsync/nodes/player/CPlayerAppearanceDataNode.hpp"
#include "netsync/nodes/player/CPlayerCameraDataNode.hpp"
#include "netsync/nodes/player/CPlayerCreationDataNode.hpp"
#include "netsync/nodes/player/CPlayerGamerDataNode.hpp"
#include "netsync/nodes/player/CPlayerGameStateDataNode.hpp"
#include "netsync/nodes/player/CPlayerPedGroupDataNode.hpp"
#include "netsync/nodes/player/CPlayerSectorPosNode.hpp"
#include "netsync/nodes/player/CPlayerWantedAndLOSDataNode.hpp"
#include "netsync/nodes/proximity_migrateable/CGlobalFlagsDataNode.hpp"
#include "netsync/nodes/proximity_migrateable/CMigrationDataNode.hpp"
#include "netsync/nodes/proximity_migrateable/CSectorDataNode.hpp"
#include "netsync/nodes/proximity_migrateable/CSectorPositionDataNode.hpp"
#include "netsync/nodes/task/ClonedTakeOffPedVariationInfo.hpp"
#include "netsync/nodes/train/CTrainGameStateDataNode.hpp"
#include "netsync/nodes/vehicle/CVehicleCreationDataNode.hpp"
#include "netsync/nodes/vehicle/CVehicleControlDataNode.hpp"
#include "netsync/nodes/vehicle/CVehicleTaskDataNode.hpp"
#include "netsync/nodes/vehicle/CVehicleGadgetDataNode.hpp"
#include "netsync/nodes/vehicle/CVehicleProximityMigrationDataNode.hpp"
#include "netsync/nodes/vehicle/CVehicleComponentReservationDataNode.hpp"
#include "netsync/nodes/vehicle/CVehicleDamageStatusDataNode.hpp"
#include "netsync/nodes/vehicle/CVehicleSteeringDataNode.hpp"
#include "netsync/nodes/vehicle/CVehicleHealthDataNode.hpp"
#include "netsync/nodes/vehicle/CVehicleGameStateDataNode.hpp"
#include "netsync/trees/CDynamicEntitySyncTreeBase.hpp"
#include "netsync/trees/CEntitySyncTreeBase.hpp"
#include "netsync/trees/CPhysicalSyncTreeBase.hpp"
#include "netsync/trees/CProximityMigrateableSyncTreeBase.hpp"
#include "network/CCommunications.hpp"
#include "network/ChatData.hpp"
#include "network/CJoinRequestContext.hpp"
#include "network/ClanData.hpp"
#include "network/CMsgJoinResponse.hpp"
#include "network/CMsgTextMessage.hpp"
#include "network/CNetComplaintMgr.hpp"
#include "network/CNetGamePlayer.hpp"
#include "network/CNetGamePlayerDataMsg.hpp"
#include "network/CNetworkPlayerMgr.hpp"
#include "network/MatchmakingAttributes.hpp"
#include "network/MatchmakingId.hpp"
#include "network/netObject.hpp"
#include "network/netObjectIds.hpp"
#include "network/netPeerAddress.hpp"
#include "network/netPlayer.hpp"
#include "network/netPlayerMgrBase.hpp"
#include "network/netTime.hpp"
#include "network/Network.hpp"
#include "network/P2pSecurity.hpp"
#include "network/RemoteGamerInfoMsg.hpp"
#include "network/snConnectToPeerTask.hpp"
#include "network/snSession.hpp"
#include "network/netConnection.hpp"
#include "ped/CPed.hpp"
#include "ped/CPedBoneInfo.hpp"
#include "ped/CPedFactory.hpp"
#include "ped/CPedIntelligence.hpp"
#include "ped/CPedInventory.hpp"
#include "ped/CPedModelInfo.hpp"
#include "ped/CPedWeaponManager.hpp"
#include "player/CNonPhysicalPlayerData.hpp"
#include "player/CPlayerAngles.hpp"
#include "player/CPlayerInfo.hpp"
#include "rage/atArray.hpp"
#include "rage/atReferenceCounter.hpp"
#include "rage/atSingleton.hpp"
#include "rage/joaat.hpp"
#include "rage/rlGamerHandle.hpp"
#include "rage/rlGamerInfo.hpp"
#include "rage/rlGamerInfoBase.hpp"
#include "rage/rlMetric.hpp"
#include "rage/rlQueryPresenceAttributesContext.hpp"
#include "rage/rlScHandle.hpp"
#include "rage/rlSessionByGamerTaskResult.hpp"
#include "rage/rlSessionInfo.hpp"
#include "rage/rlTaskStatus.hpp"
#include "rage/sysMemAllocator.hpp"
#include "rage/vector.hpp"
#include "script/dataList.hpp"
#include "script/globals/GlobalPlayerBD.hpp"
#include "script/globals/GPBD_FM.hpp"
#include "script/globals/GPBD_FM_3.hpp"
#include "script/globals/GPBD_Kicking.hpp"
#include "script/globals/GPBD_MissionName.hpp"
#include "script/globals/GSBD.hpp"
#include "script/globals/GSBD_BlockB.hpp"
#include "script/globals/GSBD_FM.hpp"
#include "script/globals/GSBD_Kicking.hpp"
#include "script/globals/GSBD_PropertyInstances.hpp"
#include "script/globals/g_AMC_playerBD.hpp"
#include "script/CGameScriptObjInfo.hpp"
#include "script/GtaThread.hpp"
#include "script/HudColor.hpp"
#include "script/MPScriptData.hpp"
#include "script/scriptHandler.hpp"
#include "script/scriptHandlerMgr.hpp"
#include "script/scriptHandlerNetComponent.hpp"
#include "script/scriptId.hpp"
#include "script/scriptIdBase.hpp"
#include "script/scriptResource.hpp"
#include "script/scrNativeHandler.hpp"
#include "script/scrNativeRegistration.hpp"
#include "script/scrNativeRegistrationTable.hpp"
#include "script/scrProgram.hpp"
#include "script/scrProgramTable.hpp"
#include "script/scrProgramTableEntry.hpp"
#include "script/scrThread.hpp"
#include "script/scrThreadContext.hpp"
#include "script/scrVector.hpp"
#include "script/Timer.hpp"
#include "script/tlsContext.hpp"
#include "script/types.hpp"
#include "security/ObfVar.hpp"
#include "security/RageSecurity.hpp"
#include "socialclub/FriendInfo.hpp"
#include "socialclub/FriendRegistry.hpp"
#include "socialclub/ScInfo.hpp"
#include "stats/CPlayerCardStats.hpp"
#include "stats/CStatsSerializationContext.hpp"
#include "vehicle/CAdvancedData.hpp"
#include "vehicle/CBaseSubHandlingData.hpp"
#include "vehicle/CCarHandlingData.hpp"
#include "vehicle/CHandlingData.hpp"
#include "vehicle/CHandlingObject.hpp"
#include "vehicle/CVehicle.hpp"
#include "vehicle/CVehicleModelInfo.hpp"
#include "vehicle/CVehicleDriveByMetadataMgr.hpp"
#include "vehicle/CVehicleSeatMetadataMgr.hpp"
#include "vehicle/CTrainConfig.hpp"
#include "vehicle/CGetPedSeatReturnClass.hpp"
#include "weapon/CAmmoInfo.hpp"
#include "weapon/CAmmoProjectileInfo.hpp"
#include "weapon/CAmmoRocketInfo.hpp"
#include "weapon/CAmmoThrownInfo.hpp"
#include "weapon/CHomingRocketParams.hpp"
#include "weapon/CItemInfo.hpp"
#include "weapon/CWeaponBoneId.hpp"
#include "weapon/CWeaponInfo.hpp"
#include "ui/CBlipList.hpp"

// add your classes here