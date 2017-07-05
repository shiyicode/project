<GameFile>
  <PropertyGroup Name="HeroNode" Type="Node" ID="4c7156f6-ebea-43d1-b37f-ca996fb02673" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="10" Speed="1.0000" ActivedAnimationName="HeroIdle">
        <Timeline ActionTag="-1500315956" Property="Position">
          <PointFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="-1500315956" Property="FileData">
          <TextureFrame FrameIndex="0" Tween="False">
            <TextureFile Type="Normal" Path="Texture/Hero1.png" Plist="" />
          </TextureFrame>
          <TextureFrame FrameIndex="10" Tween="False">
            <TextureFile Type="Normal" Path="Texture/Hero2.png" Plist="" />
          </TextureFrame>
        </Timeline>
        <Timeline ActionTag="-1500315956" Property="BlendFunc">
          <BlendFuncFrame FrameIndex="0" Tween="False" Src="1" Dst="771" />
          <BlendFuncFrame FrameIndex="10" Tween="False" Src="1" Dst="771" />
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="HeroIdle" StartIndex="0" EndIndex="20">
          <RenderColor A="150" R="138" G="43" B="226" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Hero" Tag="27" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="HeroSprite" ActionTag="-1500315956" Tag="7" IconVisible="False" LeftMargin="-68.0000" RightMargin="-68.0000" TopMargin="-84.0000" BottomMargin="-84.0000" ctype="SpriteObjectData">
            <Size X="136.0000" Y="168.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="Texture/Hero1.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>