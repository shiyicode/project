<GameFile>
  <PropertyGroup Name="BigEnemyNode" Type="Node" ID="dc1fc7cd-9ef0-456b-8dc5-63f028e2805e" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="10" Speed="1.0000" ActivedAnimationName="BigEnemyIdle">
        <Timeline ActionTag="1678781706" Property="Position">
          <PointFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="10" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="1678781706" Property="Scale">
          <ScaleFrame FrameIndex="10" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="1678781706" Property="RotationSkew">
          <ScaleFrame FrameIndex="10" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="1678781706" Property="FileData">
          <TextureFrame FrameIndex="0" Tween="False">
            <TextureFile Type="Normal" Path="Texture/BigEnemy1.png" Plist="" />
          </TextureFrame>
          <TextureFrame FrameIndex="10" Tween="False">
            <TextureFile Type="Normal" Path="Texture/BigEnemy2.png" Plist="" />
          </TextureFrame>
        </Timeline>
        <Timeline ActionTag="1678781706" Property="BlendFunc">
          <BlendFuncFrame FrameIndex="0" Tween="False" Src="1" Dst="771" />
          <BlendFuncFrame FrameIndex="10" Tween="False" Src="1" Dst="771" />
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="BigEnemyIdle" StartIndex="0" EndIndex="20">
          <RenderColor A="150" R="250" G="250" B="210" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="BigEnemy" Tag="8" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="BigEnemySprite" ActionTag="1678781706" Tag="9" IconVisible="False" LeftMargin="-41.5000" RightMargin="-41.5000" TopMargin="-52.5000" BottomMargin="-52.5000" ctype="SpriteObjectData">
            <Size X="83.0000" Y="105.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="Texture/BigEnemy1.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>