// PixelHeader


Texture2D diffuseMap : register(t0);
Texture2D specularMap : register(t1);
Texture2D normalMap : register(t2);

SamplerState samp : register(s0);

cbuffer LightBuffer : register(b0)
{
    float3 lightDir;
    float padding;
    // float shininess;
    
    float4 ambient;
}

cbuffer MaterialBuffer : register(b1)
{
    float4 mDiffuse;
    float4 mSpecular;
    float4 mAmbient;
    
    float shininess;
    
    int hasDM0;
    int hasDM1;
    int hasDM2;

    int hasSM0;
    int hasSM1;
    int hasSM2;

    int hasNM0;
    int hasNM1;
    int hasNM2;

    int make_mode;
    int padding_mat;
}

