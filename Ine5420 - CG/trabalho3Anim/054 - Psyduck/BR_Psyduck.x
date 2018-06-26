xof 0303txt 0032

template AnimTicksPerSecond {
  <9E415A43-7BA6-4a73-8743-B73D47E88476>
  DWORD AnimTicksPerSecond;
}

template XSkinMeshHeader {
  <3cf169ce-ff7c-44ab-93c0-f78f62d172e2>
  WORD nMaxSkinWeightsPerVertex;
  WORD nMaxSkinWeightsPerFace;
  WORD nBones;
}

template SkinWeights {
  <6f0d123b-bad2-4167-a0d0-80224f25fabb>
  STRING transformNodeName;
  DWORD nWeights;
  array DWORD vertexIndices[nWeights];
  array float weights[nWeights];
  Matrix4x4 matrixOffset;
}

Frame Root {
  FrameTransformMatrix {
     1.000000, 0.000000, 0.000000, 0.000000,
     0.000000, 0.000000, 1.000000, 0.000000,
     0.000000, 1.000000,-0.000000, 0.000000,
     0.000000, 0.000000, 0.000000, 1.000000;;
  }
  Frame koduck_mat_0 {
    FrameTransformMatrix {
       1.000000, 0.000000, 0.000000, 0.000000,
       0.000000, 1.000000, 0.000000, 0.000000,
       0.000000, 0.000000, 1.000000, 0.000000,
       0.000000, 0.000000, 0.000000, 1.000000;;
    }
    Mesh { //Mesh Mesh
      135;
      -0.317608;-0.444170;-0.268448;,
       0.193011;-0.444170;-0.434358;,
       0.236865; 0.120297;-0.217991;,
      -0.317608;-0.444170;-0.268448;,
       0.236865; 0.120297;-0.217991;,
      -0.503375; 0.120297; 0.022527;,
      -0.317608;-0.444170;-0.268448;,
      -0.503375; 0.120297; 0.022527;,
      -0.317608;-0.444170; 0.268448;,
      -0.503375; 0.120297; 0.022527;,
      -0.503375; 0.120297; 0.800862;,
      -0.317608;-0.444170; 0.268448;,
      -0.317608;-0.444170; 0.268448;,
      -0.503375; 0.120297; 0.800862;,
       0.193011;-0.444170; 0.434358;,
      -0.503375; 0.120297; 0.800862;,
       0.236865; 0.120297; 1.041381;,
       0.193011;-0.444170; 0.434358;,
       0.193011;-0.444170; 0.434358;,
       0.236865; 0.120297; 1.041381;,
       0.508590;-0.444170; 0.000000;,
       0.236865; 0.120297; 1.041381;,
       0.694358; 0.120297; 0.411695;,
       0.508590;-0.444170; 0.000000;,
       0.508590;-0.444170; 0.000000;,
       0.694358; 0.120297; 0.411695;,
       0.193011;-0.444170;-0.434358;,
       0.694358; 0.120297; 0.411695;,
       0.236865; 0.120297;-0.217991;,
       0.193011;-0.444170;-0.434358;,
       0.302542; 0.965668; 0.922218;,
       0.261046; 1.026599; 0.737392;,
       0.972573; 0.965668; 0.000000;,
       0.261046; 1.026599; 0.737392;,
       0.796793; 1.026599; 0.000000;,
       0.972573; 0.965668; 0.000000;,
       0.972573; 0.965668; 0.000000;,
       0.796793; 1.026599; 0.000000;,
       0.302542; 0.965668;-0.922218;,
       0.796793; 1.026599; 0.000000;,
       0.261046; 1.026599;-0.737392;,
       0.302542; 0.965668;-0.922218;,
       0.261046; 1.026599; 0.737392;,
       0.302542; 0.965668; 0.922218;,
      -0.605810; 1.026599; 0.455733;,
       0.302542; 0.965668; 0.922218;,
      -0.781590; 0.965668; 0.569962;,
      -0.605810; 1.026599; 0.455733;,
      -0.605810; 1.026599; 0.455733;,
      -0.781590; 0.965668; 0.569962;,
      -0.605810; 1.026599;-0.455733;,
      -0.781590; 0.965668; 0.569962;,
      -0.781590; 0.965668;-0.569962;,
      -0.605810; 1.026599;-0.455733;,
      -0.605810; 1.026599;-0.455733;,
      -0.781590; 0.965668;-0.569962;,
       0.261046; 1.026599;-0.737392;,
      -0.781590; 0.965668;-0.569962;,
       0.302542; 0.965668;-0.922218;,
       0.261046; 1.026599;-0.737392;,
      -0.635486; 0.521722; 0.818618;,
      -0.781590; 0.965668; 0.569962;,
       0.268052; 0.521722; 1.112195;,
      -0.781590; 0.965668; 0.569962;,
       0.302542; 0.965668; 0.922218;,
       0.268052; 0.521722; 1.112195;,
       0.268052; 0.521722; 1.112195;,
       0.302542; 0.965668; 0.922218;,
       0.826469; 0.521722; 0.343601;,
       0.302542; 0.965668; 0.922218;,
       0.972573; 0.965668; 0.000000;,
       0.826469; 0.521722; 0.343601;,
       0.826469; 0.521722; 0.343601;,
       0.972573; 0.965668; 0.000000;,
       0.268052; 0.521722;-0.424994;,
       0.972573; 0.965668; 0.000000;,
       0.302542; 0.965668;-0.922218;,
       0.268052; 0.521722;-0.424994;,
      -0.781590; 0.965668; 0.569962;,
      -0.635486; 0.521722; 0.818618;,
      -0.781590; 0.965668;-0.569962;,
      -0.635486; 0.521722; 0.818618;,
      -0.635486; 0.521722;-0.131417;,
      -0.781590; 0.965668;-0.569962;,
      -0.781590; 0.965668;-0.569962;,
      -0.635486; 0.521722;-0.131417;,
       0.302542; 0.965668;-0.922218;,
      -0.635486; 0.521722;-0.131417;,
       0.268052; 0.521722;-0.424994;,
       0.302542; 0.965668;-0.922218;,
       0.236865; 0.120297; 1.041381;,
       0.268052; 0.521722; 1.112195;,
       0.694358; 0.120297; 0.411695;,
       0.268052; 0.521722; 1.112195;,
       0.826469; 0.521722; 0.343601;,
       0.694358; 0.120297; 0.411695;,
       0.694358; 0.120297; 0.411695;,
       0.826469; 0.521722; 0.343601;,
       0.236865; 0.120297;-0.217991;,
       0.826469; 0.521722; 0.343601;,
       0.268052; 0.521722;-0.424994;,
       0.236865; 0.120297;-0.217991;,
       0.268052; 0.521722; 1.112195;,
       0.236865; 0.120297; 1.041381;,
      -0.635486; 0.521722; 0.818618;,
       0.236865; 0.120297; 1.041381;,
      -0.503375; 0.120297; 0.800862;,
      -0.635486; 0.521722; 0.818618;,
      -0.635486; 0.521722; 0.818618;,
      -0.503375; 0.120297; 0.800862;,
      -0.635486; 0.521722;-0.131417;,
      -0.503375; 0.120297; 0.800862;,
      -0.503375; 0.120297; 0.022527;,
      -0.635486; 0.521722;-0.131417;,
      -0.635486; 0.521722;-0.131417;,
      -0.503375; 0.120297; 0.022527;,
       0.268052; 0.521722;-0.424994;,
      -0.503375; 0.120297; 0.022527;,
       0.236865; 0.120297;-0.217991;,
       0.268052; 0.521722;-0.424994;,
       0.261046; 1.026599;-0.737392;,
       0.000000; 1.078148; 0.000000;,
      -0.605810; 1.026599;-0.455733;,
       0.000000; 1.078148; 0.000000;,
      -0.605810; 1.026599; 0.455733;,
      -0.605810; 1.026599;-0.455733;,
      -0.605810; 1.026599; 0.455733;,
       0.000000; 1.078148; 0.000000;,
       0.261046; 1.026599; 0.737392;,
       0.000000; 1.078148; 0.000000;,
       0.796793; 1.026599; 0.000000;,
       0.261046; 1.026599; 0.737392;,
       0.796793; 1.026599; 0.000000;,
       0.000000; 1.078148; 0.000000;,
       0.261046; 1.026599;-0.737392;;
      45;
      3;0;1;2;,
      3;3;4;5;,
      3;6;7;8;,
      3;9;10;11;,
      3;12;13;14;,
      3;15;16;17;,
      3;18;19;20;,
      3;21;22;23;,
      3;24;25;26;,
      3;27;28;29;,
      3;30;31;32;,
      3;33;34;35;,
      3;36;37;38;,
      3;39;40;41;,
      3;42;43;44;,
      3;45;46;47;,
      3;48;49;50;,
      3;51;52;53;,
      3;54;55;56;,
      3;57;58;59;,
      3;60;61;62;,
      3;63;64;65;,
      3;66;67;68;,
      3;69;70;71;,
      3;72;73;74;,
      3;75;76;77;,
      3;78;79;80;,
      3;81;82;83;,
      3;84;85;86;,
      3;87;88;89;,
      3;90;91;92;,
      3;93;94;95;,
      3;96;97;98;,
      3;99;100;101;,
      3;102;103;104;,
      3;105;106;107;,
      3;108;109;110;,
      3;111;112;113;,
      3;114;115;116;,
      3;117;118;119;,
      3;120;121;122;,
      3;123;124;125;,
      3;126;127;128;,
      3;129;130;131;,
      3;132;133;134;;
      MeshNormals { //Mesh Normals
        135;
         0.671834;-0.152532; 0.724815;,
        -0.239784;-0.331156; 0.912564;,
        -0.363628; 0.093570; 0.926817;,
         0.671834;-0.152532; 0.724815;,
        -0.363628; 0.093570; 0.926817;,
         0.838679; 0.284921; 0.464095;,
         0.671834;-0.152532; 0.724815;,
         0.838679; 0.284921; 0.464095;,
         0.765740; 0.556322;-0.322642;,
         0.838679; 0.284921; 0.464095;,
         0.677511; 0.445692;-0.585040;,
         0.765740; 0.556322;-0.322642;,
         0.765740; 0.556322;-0.322642;,
         0.677511; 0.445692;-0.585040;,
        -0.289193; 0.711325;-0.640553;,
         0.677511; 0.445692;-0.585040;,
        -0.259468; 0.437635;-0.860866;,
        -0.289193; 0.711325;-0.640553;,
        -0.289193; 0.711325;-0.640553;,
        -0.259468; 0.437635;-0.860866;,
        -0.958708; 0.131748; 0.251930;,
        -0.259468; 0.437635;-0.860866;,
        -0.928434; 0.353587;-0.113712;,
        -0.958708; 0.131748; 0.251930;,
        -0.958708; 0.131748; 0.251930;,
        -0.928434; 0.353587;-0.113712;,
        -0.239784;-0.331156; 0.912564;,
        -0.928434; 0.353587;-0.113712;,
        -0.363628; 0.093570; 0.926817;,
        -0.239784;-0.331156; 0.912564;,
        -0.285684;-0.644673;-0.709037;,
        -0.087558;-0.971709;-0.219275;,
        -0.939756;-0.310343; 0.143132;,
        -0.087558;-0.971709;-0.219275;,
        -0.247963;-0.968749;-0.000000;,
        -0.939756;-0.310343; 0.143132;,
        -0.939756;-0.310343; 0.143132;,
        -0.247963;-0.968749;-0.000000;,
        -0.266427;-0.164861; 0.949614;,
        -0.247963;-0.968749;-0.000000;,
        -0.087558;-0.971709; 0.219275;,
        -0.266427;-0.164861; 0.949614;,
        -0.087558;-0.971709;-0.219275;,
        -0.285684;-0.644673;-0.709037;,
         0.169927;-0.976379;-0.133366;,
        -0.285684;-0.644673;-0.709037;,
         0.791223;-0.477371;-0.382153;,
         0.169927;-0.976379;-0.133366;,
         0.169927;-0.976379;-0.133366;,
         0.791223;-0.477371;-0.382153;,
         0.169927;-0.976379; 0.133366;,
         0.791223;-0.477371;-0.382153;,
         0.738701;-0.211829; 0.639851;,
         0.169927;-0.976379; 0.133366;,
         0.169927;-0.976379; 0.133366;,
         0.738701;-0.211829; 0.639851;,
        -0.087558;-0.971709; 0.219275;,
         0.738701;-0.211829; 0.639851;,
        -0.266427;-0.164861; 0.949614;,
        -0.087558;-0.971709; 0.219275;,
         0.758415; 0.046480;-0.650075;,
         0.791223;-0.477371;-0.382153;,
        -0.284433;-0.084689;-0.954924;,
         0.791223;-0.477371;-0.382153;,
        -0.285684;-0.644673;-0.709037;,
        -0.284433;-0.084689;-0.954924;,
        -0.284433;-0.084689;-0.954924;,
        -0.285684;-0.644673;-0.709037;,
        -0.969817; 0.210669;-0.122623;,
        -0.285684;-0.644673;-0.709037;,
        -0.939756;-0.310343; 0.143132;,
        -0.969817; 0.210669;-0.122623;,
        -0.969817; 0.210669;-0.122623;,
        -0.939756;-0.310343; 0.143132;,
        -0.278848; 0.633412; 0.721793;,
        -0.939756;-0.310343; 0.143132;,
        -0.266427;-0.164861; 0.949614;,
        -0.278848; 0.633412; 0.721793;,
         0.791223;-0.477371;-0.382153;,
         0.758415; 0.046480;-0.650075;,
         0.738701;-0.211829; 0.639851;,
         0.758415; 0.046480;-0.650075;,
         0.749809; 0.518998; 0.410321;,
         0.738701;-0.211829; 0.639851;,
         0.738701;-0.211829; 0.639851;,
         0.749809; 0.518998; 0.410321;,
        -0.266427;-0.164861; 0.949614;,
         0.749809; 0.518998; 0.410321;,
        -0.278848; 0.633412; 0.721793;,
        -0.266427;-0.164861; 0.949614;,
        -0.259468; 0.437635;-0.860866;,
        -0.284433;-0.084689;-0.954924;,
        -0.928434; 0.353587;-0.113712;,
        -0.284433;-0.084689;-0.954924;,
        -0.969817; 0.210669;-0.122623;,
        -0.928434; 0.353587;-0.113712;,
        -0.928434; 0.353587;-0.113712;,
        -0.969817; 0.210669;-0.122623;,
        -0.363628; 0.093570; 0.926817;,
        -0.969817; 0.210669;-0.122623;,
        -0.278848; 0.633412; 0.721793;,
        -0.363628; 0.093570; 0.926817;,
        -0.284433;-0.084689;-0.954924;,
        -0.259468; 0.437635;-0.860866;,
         0.758415; 0.046480;-0.650075;,
        -0.259468; 0.437635;-0.860866;,
         0.677511; 0.445692;-0.585040;,
         0.758415; 0.046480;-0.650075;,
         0.758415; 0.046480;-0.650075;,
         0.677511; 0.445692;-0.585040;,
         0.749809; 0.518998; 0.410321;,
         0.677511; 0.445692;-0.585040;,
         0.838679; 0.284921; 0.464095;,
         0.749809; 0.518998; 0.410321;,
         0.749809; 0.518998; 0.410321;,
         0.838679; 0.284921; 0.464095;,
        -0.278848; 0.633412; 0.721793;,
         0.838679; 0.284921; 0.464095;,
        -0.363628; 0.093570; 0.926817;,
        -0.278848; 0.633412; 0.721793;,
        -0.087558;-0.971709; 0.219275;,
         0.002441;-0.999969;-0.000000;,
         0.169927;-0.976379; 0.133366;,
         0.002441;-0.999969;-0.000000;,
         0.169927;-0.976379;-0.133366;,
         0.169927;-0.976379; 0.133366;,
         0.169927;-0.976379;-0.133366;,
         0.002441;-0.999969;-0.000000;,
        -0.087558;-0.971709;-0.219275;,
         0.002441;-0.999969;-0.000000;,
        -0.247963;-0.968749;-0.000000;,
        -0.087558;-0.971709;-0.219275;,
        -0.247963;-0.968749;-0.000000;,
         0.002441;-0.999969;-0.000000;,
        -0.087558;-0.971709; 0.219275;;
        45;
        3;0;1;2;,
        3;3;4;5;,
        3;6;7;8;,
        3;9;10;11;,
        3;12;13;14;,
        3;15;16;17;,
        3;18;19;20;,
        3;21;22;23;,
        3;24;25;26;,
        3;27;28;29;,
        3;30;31;32;,
        3;33;34;35;,
        3;36;37;38;,
        3;39;40;41;,
        3;42;43;44;,
        3;45;46;47;,
        3;48;49;50;,
        3;51;52;53;,
        3;54;55;56;,
        3;57;58;59;,
        3;60;61;62;,
        3;63;64;65;,
        3;66;67;68;,
        3;69;70;71;,
        3;72;73;74;,
        3;75;76;77;,
        3;78;79;80;,
        3;81;82;83;,
        3;84;85;86;,
        3;87;88;89;,
        3;90;91;92;,
        3;93;94;95;,
        3;96;97;98;,
        3;99;100;101;,
        3;102;103;104;,
        3;105;106;107;,
        3;108;109;110;,
        3;111;112;113;,
        3;114;115;116;,
        3;117;118;119;,
        3;120;121;122;,
        3;123;124;125;,
        3;126;127;128;,
        3;129;130;131;,
        3;132;133;134;;
      } //End of Mesh Normals
      MeshMaterialList { //Mesh Material List
        1;
        45;
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0;;
        Material mat_0 {
           0.640000; 0.640000; 0.640000; 1.000000;;
           92.156863;
           0.250000; 0.250000; 0.250000;;
           0.000000; 0.000000; 0.000000;;
          TextureFilename {"Textures/koduck_0_0.tga";}
        }
      } //End of Mesh Material List
      MeshTextureCoords { //Mesh UV Coordinates
        135;
         0.893046; 0.483350;,
         0.893046; 0.435026;,
         0.906596; 0.483350;,
         0.906596; 0.483350;,
         0.893046; 0.435026;,
         0.906596; 0.435026;,
         0.906596; 0.483350;,
         0.906596; 0.435026;,
         0.920146; 0.483350;,
         0.906596; 0.435026;,
         0.920146; 0.435026;,
         0.920146; 0.483350;,
         0.920146; 0.483350;,
         0.920146; 0.435026;,
         0.933695; 0.483350;,
         0.920146; 0.435026;,
         0.933695; 0.435026;,
         0.933695; 0.483350;,
         0.933695; 0.483350;,
         0.933695; 0.435026;,
         0.947245; 0.483350;,
         0.933695; 0.435026;,
         0.947245; 0.435026;,
         0.947245; 0.483350;,
         0.947245; 0.483350;,
         0.947245; 0.435026;,
         0.960795; 0.483350;,
         0.947245; 0.435026;,
         0.960795; 0.435026;,
         0.960795; 0.483350;,
         0.933695; 0.362654;,
         0.931853; 0.351026;,
         0.947245; 0.362654;,
         0.931853; 0.351026;,
         0.941718; 0.351026;,
         0.947245; 0.362654;,
         0.947245; 0.362654;,
         0.941718; 0.351026;,
         0.960795; 0.362654;,
         0.941718; 0.351026;,
         0.951583; 0.351026;,
         0.960795; 0.362654;,
         0.931853; 0.351026;,
         0.933695; 0.362654;,
         0.921988; 0.351026;,
         0.933695; 0.362654;,
         0.920146; 0.362654;,
         0.921988; 0.351026;,
         0.921988; 0.351026;,
         0.920146; 0.362654;,
         0.912123; 0.351026;,
         0.920146; 0.362654;,
         0.906596; 0.362654;,
         0.912123; 0.351026;,
         0.912123; 0.351026;,
         0.906596; 0.362654;,
         0.902258; 0.351026;,
         0.906596; 0.362654;,
         0.893046; 0.362654;,
         0.902258; 0.351026;,
         0.920146; 0.400660;,
         0.920146; 0.362654;,
         0.933695; 0.400660;,
         0.920146; 0.362654;,
         0.933695; 0.362654;,
         0.933695; 0.400660;,
         0.933695; 0.400660;,
         0.933695; 0.362654;,
         0.947245; 0.400660;,
         0.933695; 0.362654;,
         0.947245; 0.362654;,
         0.947245; 0.400660;,
         0.947245; 0.400660;,
         0.947245; 0.362654;,
         0.960795; 0.400660;,
         0.947245; 0.362654;,
         0.960795; 0.362654;,
         0.960795; 0.400660;,
         0.920146; 0.362654;,
         0.920146; 0.400660;,
         0.906596; 0.362654;,
         0.920146; 0.400660;,
         0.906596; 0.400660;,
         0.906596; 0.362654;,
         0.906596; 0.362654;,
         0.906596; 0.400660;,
         0.893046; 0.362654;,
         0.906596; 0.400660;,
         0.893046; 0.400660;,
         0.893046; 0.362654;,
         0.933695; 0.435026;,
         0.933695; 0.400660;,
         0.947245; 0.435026;,
         0.933695; 0.400660;,
         0.947245; 0.400660;,
         0.947245; 0.435026;,
         0.947245; 0.435026;,
         0.947245; 0.400660;,
         0.960795; 0.435026;,
         0.947245; 0.400660;,
         0.960795; 0.400660;,
         0.960795; 0.435026;,
         0.933695; 0.400660;,
         0.933695; 0.435026;,
         0.920146; 0.400660;,
         0.933695; 0.435026;,
         0.920146; 0.435026;,
         0.920146; 0.400660;,
         0.920146; 0.400660;,
         0.920146; 0.435026;,
         0.906596; 0.400660;,
         0.920146; 0.435026;,
         0.906596; 0.435026;,
         0.906596; 0.400660;,
         0.906596; 0.400660;,
         0.906596; 0.435026;,
         0.893046; 0.400660;,
         0.906596; 0.435026;,
         0.893046; 0.435026;,
         0.893046; 0.400660;,
         0.902258; 0.351026;,
         0.926921; 0.341133;,
         0.912123; 0.351026;,
         0.926921; 0.341133;,
         0.921988; 0.351026;,
         0.912123; 0.351026;,
         0.921988; 0.351026;,
         0.926921; 0.341133;,
         0.931853; 0.351026;,
         0.926921; 0.341133;,
         0.941718; 0.351026;,
         0.931853; 0.351026;,
         0.941718; 0.351026;,
         0.926921; 0.341133;,
         0.951583; 0.351026;;
      } //End of Mesh UV Coordinates
    } //End of Mesh Mesh
  } //End of koduck_mat_0
} //End of Root Frame
