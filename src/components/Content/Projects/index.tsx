import { Box, styled } from "@mui/material";
import { SectionWrapper, TitleWrapper } from "../../../styles/sectionStyles";
import { Project } from "./Project";
import projects from "./Projects.json";
export const ProjectsContainer = () => {
  return (
    <SectionWrapper>
      <TitleWrapper>PROJECTS</TitleWrapper>
      <Box>
        {projects.map((project) => (
          <Project project={project} />
        ))}
      </Box>
    </SectionWrapper>
  );
};