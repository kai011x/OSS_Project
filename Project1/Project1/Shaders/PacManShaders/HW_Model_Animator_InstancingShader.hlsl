
// ModelAnimator
#include "../VertexHeader.hlsli"
#include "../PixelHeader.hlsli"

struct VertexInput
{
    float4 pos : POSITION;
    float2 uv : UV;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float4 indices : BLENDINDICES;
    float4 weights : BLENDWEIGHTS;
    
    matrix transform : INSTANCE_TRANSFORM;
};


struct PixelInput
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float3 binormal : BINORMAL;
    float3 viewDir : VIEWDIR;
};

matrix SkinWorld(float4 indices, float4 weights)
{
    matrix transform = 0;
    matrix cur, next;
    matrix curAnim, nextAnim;
    
    float4 c0, c1, c2, c3;
    float4 n0, n1, n2, n3;
    
    for (int i = 0; i < 4; i++)
    {
        int curFrame = motion.cur.curFrame;
        int clip = motion.cur.clip;
        
        c0 = transformMap.Load(int4(indices[i] * 4 + 0, curFrame, clip, 0));
        c1 = transformMap.Load(int4(indices[i] * 4 + 1, curFrame, clip, 0));
        c2 = transformMap.Load(int4(indices[i] * 4 + 2, curFrame, clip, 0));
        c3 = transformMap.Load(int4(indices[i] * 4 + 3, curFrame, clip, 0));
        
        cur = matrix(c0, c1, c2, c3);
        
        n0 = transformMap.Load(int4(indices[i] * 4 + 0, curFrame + 1, clip, 0));
        n1 = transformMap.Load(int4(indices[i] * 4 + 1, curFrame + 1, clip, 0));
        n2 = transformMap.Load(int4(indices[i] * 4 + 2, curFrame + 1, clip, 0));
        n3 = transformMap.Load(int4(indices[i] * 4 + 3, curFrame + 1, clip, 0));
        
        next = matrix(n0, n1, n2, n3);
        
        curAnim = lerp(cur, next, motion.cur.time);
        /*=======================================================================*/
        curFrame = motion.next.curFrame;
        clip = motion.next.clip;
        
        if (clip > -1)
        {
            c0 = transformMap.Load(int4(indices[i] * 4 + 0, curFrame, clip, 0));
            c1 = transformMap.Load(int4(indices[i] * 4 + 1, curFrame, clip, 0));
            c2 = transformMap.Load(int4(indices[i] * 4 + 2, curFrame, clip, 0));
            c3 = transformMap.Load(int4(indices[i] * 4 + 3, curFrame, clip, 0));
        
            cur = matrix(c0, c1, c2, c3);
        
            n0 = transformMap.Load(int4(indices[i] * 4 + 0, curFrame + 1, clip, 0));
            n1 = transformMap.Load(int4(indices[i] * 4 + 1, curFrame + 1, clip, 0));
            n2 = transformMap.Load(int4(indices[i] * 4 + 2, curFrame + 1, clip, 0));
            n3 = transformMap.Load(int4(indices[i] * 4 + 3, curFrame + 1, clip, 0));
        
            next = matrix(n0, n1, n2, n3);
        
            nextAnim = lerp(cur, next, motion.next.time);
            
            curAnim = lerp(curAnim, nextAnim, motion.tweenTIme);
        }
        
        transform += mul(weights[i], curAnim);
    }
    
    return transform;
}

PixelInput VS(VertexInput input)
{
    PixelInput output;
    
    matrix transform = mul(SkinWorld(input.indices, input.weights), input.transform);
    output.pos = mul(input.pos, transform);
  
    output.viewDir = normalize(output.pos.xyz - invView._41_42_43);
    
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, projection);

    output.uv = input.uv;
    
    output.normal = mul(input.normal, (float3x3) input.transform);
    output.tangent = mul(input.tangent, (float3x3) input.transform);
    output.binormal = cross(output.normal, output.tangent);
    
    return output;

}

float4 PS(PixelInput input) : SV_TARGET // 색의 영역
{
    float4 albedo = float4(1, 1, 1, 1);
    
    if (hasDM0)
        albedo = diffuseMap.Sample(samp, input.uv);
    
    float3 normal = normalize(input.normal);

    if (hasNM0)
    {
        float3 T = normalize(input.tangent); // x축
        float3 B = normalize(input.binormal); // y축
        float3 N = normalize(input.normal); //z축에 해당
        float3x3 TBN = float3x3(T, B, N);

        float4 normalMapping = normalMap.Sample(samp, input.uv);
        normal = normalMapping.rgb * 2.0f - 1.0f; // 0~1 -> -1 ~ 1로 바꾸기
        normal = normalize(mul(normal, TBN));
    }
    
    float3 light = normalize(lightDir);
    
    float diffuse = saturate(dot(normal, -light));

    float4 specular = 0;
    if (diffuse > 0.0f)  // 빛이 들어 온다면
    {
        float3 reflection = normalize(reflect(light, normal));
        specular = saturate(dot(-reflection, input.viewDir));
        
        float4 specularIntensity = float4(1, 1, 1, 1);
        if (hasSM0)
            specularIntensity = specularMap.Sample(samp, input.uv);
        
        // ^ = pow
        specular = pow(specular, shininess) * specularIntensity;
    }
    
    float4 diffuseColor = albedo * diffuse * mDiffuse;
    float4 specularColor = specular * mSpecular;
    float4 ambientColor = albedo * ambient * mAmbient;
    
    return diffuseColor + specularColor + ambientColor;

}