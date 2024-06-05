# OSS_Project
 
구현 목표 : DirectX3D를 활용한 1인칭 3D pacman 게임입니다. 3가지 몬스터를 피해 5목숨안에 모든 코인을 다먹으면 승리합니다. 

구현 기능 
* 키보드로 1인칭의 플레이어를 조작 가능
* 플레이어를 인식하면 Astar algoritmn을 통해 쫒아오는 몬스터 구현, 몬스터는 플레이어를 일정시간 쫒아오다가 다시 patrol 모드로 돌아감
* shader를 통한 실제적인 질감과 광원효과 추가
* 플레이어의 위치와 코인의 위치를 확인할 수 있는 미니맵 구현
* Vector 와 Matrix를 통한 충돌처리 계산

실행방법:
모든 파일을 다운 받은 후 solution을 켜서 빌드후 실행하면 된다. 

실행예시:
![image](https://github.com/kai011x/OSS_Project/assets/48053180/c96a0108-c709-4e0a-a1ea-09d6e601cefc)
![image](https://github.com/kai011x/OSS_Project/assets/48053180/c96a0108-c709-4e0a-a1ea-09d6e601cefc)


코드설명:
FrameWork 폴더 안의 파일들을 통해 Direct3DX의 Rendering pipeline을 실행한다.(건드릴 필요 없음) 
GridScne.cpp를 통해 맵을 가져올 수 있다.(건드릴 필요 없음)

HW_Scene.cpp 을 통해 Game의 System을 수정할 수 있다. 
HW_Scene.cpp 에서 Monster 움직임도 제어.
HW_Character_Transform.cpp를 통해 1인칭 플레이어의 움직임을 제어할 수 있다. 
HW_Pacman_Map.cpp를 통해 Map에 요소를 추가하거나 제거할 수 있음. 

새로운 Item이나 몬스터 등 객체를 Map 위에 올리려면 반드시 class를 생성할 때, Transform 클래스를 상속받아서 생성한다.  
Transform 클래스 안에 UpdateWorld() 함수를 Scene의 Update() 함수 안에서 실행시켜줘야 매 프레임마다 움직임이 새로 계산되어 적용된다.
새로 만드는 객체에 다른 객체들과 상호작용을 하기 위해서는 FrameWork->Collision 폴더 안에 있는 3가지 Collider 중에 하나를 멤버변수로 가져야 한다. 
모든 Colldier는 각 Collider에 맞는 계산 함수가 있으니 그것을 활용하면 된다.

Collider에는 GetMaterial()->SetDiffuseMap()을 통해 collider의 이미지를 입힐 수 있다.
그후 GetMaterial()->SetShader()를 통해 사용할 Shader를 설정해야 된다. 

To_do List:
달리기 추가
새로운 아이템 추가
새로운 능력 추가
