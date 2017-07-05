<GameFile>
  <PropertyGroup Name="SmallEnemyNode" Type="Node" ID="63ba446f-da05-4e6c-a62c-c41f9625d848" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="10" Speed="1.0000" ActivedAnimationName="SmallEnemyIdle">
        <Timeline ActionTag="-1091108810" Property="Position">
          <PointFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="-1091108810" Property="FileData">
          <TextureFrame FrameIndex="0" Tween="False">
            <TextureFile Type="Normal" Path="Texture/SmallEnemy1.png" Plist="" />
          </TextureFrame>
          <TextureFrame FrameIndex="10" Tween="False">
            <TextureFile Type="Normal" Path="Texture/SmallEnemy2.png" Plist="" />
          </TextureFrame>
        </Timeline>
        <Timeline ActionTag="-1091108810" Property="BlendFunc">
          <BlendFuncFrame FrameIndex="0" Tween="False" Src="1" Dst="771" />
          <BlendFuncFrame FrameIndex="10" Tween="False" Src="1" Dst="771" />
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="SmallEnemyIdle" StartIndex="0" EndIndex="20">
          <RenderColor A="150" R="160" G="82" B="45" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="SmallEnemyNode" Tag="10" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="SmallEnemySprite" ActionTag="-1091108810" Tag="11" IconVisible="False" LeftMargin="-35.5000" RightMargin="-35.5000" TopMargin="-36.5000" BottomMargin="-36.5000" ctype="SpriteObjectData">
            <Size X="71.0000" Y="73.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="Texture/SmallEnemy2.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>