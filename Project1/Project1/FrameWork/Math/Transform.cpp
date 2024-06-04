#include "Framework.h"

Transform::Transform(): local_Scale(1,1,1)
{
	world = XMMatrixIdentity();
}

Transform::~Transform()
{
}

void Transform::UpdateWorld()
{
    if (!Active())return;

    world = XMMatrixTransformation(
        pivotS,
        XMQuaternionIdentity(), 
        local_Scale, 
        pivotR,
        XMQuaternionRotationRollPitchYaw(local_Rotation.x, local_Rotation.y, local_Rotation.z),
        local_Position);
//    Matrix T = XMMatrixTranslation(local_Position.x, local_Position.y, local_Position.z);
//    Matrix R = XMMatrixRotationRollPitchYawFromVector(local_Rotation);
//    Matrix S = XMMatrixScaling(local_Scale.x, local_Scale.y, local_Scale.z);

    //XMQuaternionRotationRollPitchYawFromVector
    if (parent != nullptr)
        world *= (*parent);
    
    XMMatrixDecompose(globalScale.GetData(), globalRotation.GetData(), globalPosition.GetData(), world);
}

void Transform::GUIRender()
{
    if (ImGui::TreeNode((tag + "_Transform").c_str()))
    {
        ImGui::Checkbox(tag.c_str(), &isActive);
        ImGui::DragFloat3((tag + "_Pos").c_str(), (float*)&local_Position, 0.1f);

        Vector3 degree;
        degree.x = XMConvertToDegrees(local_Rotation.x);
        degree.y = XMConvertToDegrees(local_Rotation.y);
        degree.z = XMConvertToDegrees(local_Rotation.z);

        ImGui::DragFloat3((tag + "_Rot").c_str(), (float*)&degree, 0.1f);

        local_Rotation.x = XMConvertToRadians(degree.x);
        local_Rotation.y = XMConvertToRadians(degree.y);
        local_Rotation.z = XMConvertToRadians(degree.z);

        ImGui::DragFloat3((tag + "_Scal").c_str(), (float*)&local_Scale, 0.1f);

        if (ImGui::Button("Save"))
            Save();
        ImGui::SameLine();
        if (ImGui::Button("Load"))
            Load();

        ImGui::TreePop();
    }
}

Vector3 Transform::Forward()
{
    // º¤ÅÍ¶û matrix¶û °öÇÏ´Â ¹æ¹ý (Áß¿ä)
    return (Vector3(0, 0, 1) * world).Normalize();
}

Vector3 Transform::Right()
{
    return (Vector3(1, 0, 0) * world).Normalize();
}

Vector3 Transform::Up()
{
    return (Vector3(0, 1, 0) * world).Normalize();
}

void Transform::Save()
{
    BinaryWriter* writer = new BinaryWriter("TextData/Transforms/" + tag + ".srt");

    writer->Vector(local_Position);
    writer->Vector(local_Rotation);
    writer->Vector(local_Scale);

    delete writer;
}

void Transform::Load()
{
    BinaryReader* reader = new BinaryReader("TextData/Transforms/" + tag + ".srt");

    if (reader->IsFailed())return;

    local_Position = reader->Vector();
    local_Rotation = reader->Vector();
    local_Scale = reader->Vector();

    delete reader;

    this->UpdateWorld();
}

bool Transform::Active()
{
    if (parentTransform == nullptr)
        return isActive;
    
    if (!isActive)
        return false;

    return parentTransform->Active();
}
