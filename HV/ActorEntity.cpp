#include "ActorEntity.h"
#include "offset.h"


FMatrix FTransform::ToMatrixWithScale()
{
	FMatrix m;

	m._41 = Translation.X;
	m._42 = Translation.Y;
	m._43 = Translation.Z;

	float x2 = Rotation.X + Rotation.X;
	float y2 = Rotation.Y + Rotation.Y;
	float z2 = Rotation.Z + Rotation.Z;

	float xx2 = Rotation.X * x2;
	float yy2 = Rotation.Y * y2;
	float zz2 = Rotation.Z * z2;
	m._11 = (1.0f - (yy2 + zz2)) * Scale3D.X;
	m._22 = (1.0f - (xx2 + zz2)) * Scale3D.Y;
	m._33 = (1.0f - (xx2 + yy2)) * Scale3D.Z;


	float yz2 = Rotation.Y * z2;
	float wx2 = Rotation.W * x2;
	m._32 = (yz2 - wx2) * Scale3D.Z;
	m._23 = (yz2 + wx2) * Scale3D.Y;


	float xy2 = Rotation.X * y2;
	float wz2 = Rotation.W * z2;
	m._21 = (xy2 - wz2) * Scale3D.Y;
	m._12 = (xy2 + wz2) * Scale3D.X;


	float xz2 = Rotation.X * z2;
	float wy2 = Rotation.W * y2;
	m._31 = (xz2 + wy2) * Scale3D.Z;
	m._13 = (xz2 - wy2) * Scale3D.X;

	m._14 = 0.0f;
	m._24 = 0.0f;
	m._34 = 0.0f;
	m._44 = 1.0f;

	return m;
}

void GetIndex(Index& index)
{
	index.Head = 35;
	index.neck = 5;
	index.pelvis = 1;
	index.Lshoulder = 88;
	index.Lelbow = 89;
	index.Lhand = 90;
	index.Rshoulder = 115;
	index.Relbow = 116;
	index.Rhand = 117;
	index.Lbuttock = 177;
	index.Lknee = 173;
	index.Lfoot = 174;
	index.Rbuttock = 183;
	index.Rknee = 179;
	index.Rfoot = 180;

}



FMatrix FMatrix::MatrixMultiplication(const FMatrix& other)
{
	FMatrix NewMatrix;

	NewMatrix._11 = this->_11 * other._11 + this->_12 * other._21 + this->_13 * other._31 + this->_14 * other._41;
	NewMatrix._12 = this->_11 * other._12 + this->_12 * other._22 + this->_13 * other._32 + this->_14 * other._42;
	NewMatrix._13 = this->_11 * other._13 + this->_12 * other._23 + this->_13 * other._33 + this->_14 * other._43;
	NewMatrix._14 = this->_11 * other._14 + this->_12 * other._24 + this->_13 * other._34 + this->_14 * other._44;
	NewMatrix._21 = this->_21 * other._11 + this->_22 * other._21 + this->_23 * other._31 + this->_24 * other._41;
	NewMatrix._22 = this->_21 * other._12 + this->_22 * other._22 + this->_23 * other._32 + this->_24 * other._42;
	NewMatrix._23 = this->_21 * other._13 + this->_22 * other._23 + this->_23 * other._33 + this->_24 * other._43;
	NewMatrix._24 = this->_21 * other._14 + this->_22 * other._24 + this->_23 * other._34 + this->_24 * other._44;
	NewMatrix._31 = this->_31 * other._11 + this->_32 * other._21 + this->_33 * other._31 + this->_34 * other._41;
	NewMatrix._32 = this->_31 * other._12 + this->_32 * other._22 + this->_33 * other._32 + this->_34 * other._42;
	NewMatrix._33 = this->_31 * other._13 + this->_32 * other._23 + this->_33 * other._33 + this->_34 * other._43;
	NewMatrix._34 = this->_31 * other._14 + this->_32 * other._24 + this->_33 * other._34 + this->_34 * other._44;
	NewMatrix._41 = this->_41 * other._11 + this->_42 * other._21 + this->_43 * other._31 + this->_44 * other._41;
	NewMatrix._42 = this->_41 * other._12 + this->_42 * other._22 + this->_43 * other._32 + this->_44 * other._42;
	NewMatrix._43 = this->_41 * other._13 + this->_42 * other._23 + this->_43 * other._33 + this->_44 * other._43;
	NewMatrix._44 = this->_41 * other._14 + this->_42 * other._24 + this->_43 * other._34 + this->_44 * other._44;

	return NewMatrix;
}

ActorEntity::ActorEntity(uint64_t address)
{
	Class = address;
	if (!address)
		return;

	//TargetProcess.AddScatterReadRequest(handle, Class + SDK.PlayerState, reinterpret_cast<void*>(&PlayerState), sizeof(uint64_t));
	//TargetProcess.AddScatterReadRequest(handle, Class + SDK.AcknowledgedPawn, reinterpret_cast<void*>(&AcknowledgedPawn), sizeof(uint64_t));
	//TargetProcess.AddScatterReadRequest(handle, Class + SDK.RootComponent, reinterpret_cast<void*>(&RootComponent), sizeof(uint64_t));
	//TargetProcess.AddScatterReadRequest(handle, Class + SDK.Mesh, reinterpret_cast<void*>(&Mesh), sizeof(uint64_t));
	//TargetProcess.AddScatterReadRequest(handle, Class + SDK.LastTeamNum, reinterpret_cast<void*>(&LastTeamNum), sizeof(uint64_t));

	HV::ReadMemory(Class+ SDK::PlayerState, reinterpret_cast<ULONG64>(&PlayerState), sizeof(uint64_t));
	HV::ReadMemory(Class + SDK::AcknowledgedPawn, reinterpret_cast<ULONG64>(&AcknowledgedPawn), sizeof(uint64_t));
	HV::ReadMemory(Class + SDK::RootComponent, reinterpret_cast<ULONG64>(&RootComponent), sizeof(uint64_t));
	HV::ReadMemory(Class + SDK::Mesh, reinterpret_cast<ULONG64>(&Mesh), sizeof(uint64_t));

	HV::ReadMemory(Class + SDK::LastTeamNum, reinterpret_cast<ULONG64>(&LastTeamNum), sizeof(uint64_t));

	GetIndex(index);
}

void ActorEntity::SetUp1()
{
}
