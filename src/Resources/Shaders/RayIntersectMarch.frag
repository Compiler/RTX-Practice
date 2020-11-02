

vec3 phongIllumination(vec3 ka, vec3 kd, vec3 ks, float laphha)


vec2 iResolution = vec2(640, 480);

int main (){

    vec2 uv = (gl_FragCoord.xy - 0.5 * iResolution.xy) / iResolution.y;

    vec3 resultingColor = vec3(0);

    Ray cameraRay;
    cev3 cameraPos = vec3(0., 3., -2.); vec3 lookAt = vec3(0., 2.5, 0.); float zoom = 1;

    cameraRay = getRay(uv, cameraPos, lookAt, zoom); //todo implement lmfao

    RayHit rayMarch = rayMarch(cameraRay);

    vec3 point = cameraRay.origin + (cameraRay.direction * rayMarch.dist);
    vec3 ka  = vec3(0.005);
    vec3 ks = vec3(1., 0.1, 0.1);
    float s = 3.;

    vec3 color = phongIllumination(kla, rayMarch.color, ks, s, point, cameraRay.origin);
    outColor = vec4(color, 1.0);


}