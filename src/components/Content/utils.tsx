import Education from "../../assets/education.png";
import Skills from "../../assets/skills.png";
import Person from "../../assets/hacker.png";
import Experience from "../../assets/experience.png";
import Projects from "../../assets/idea.png";
import Achievements from "../../assets/growth.png";
import { AboutMe } from "./AboutMe";
import ExperienceContainer from "./Experience";
import { ProjectsContainer } from "./Projects";
import { EducationContainer } from "./Education";
import { SkillsContainer } from "./Skills";

interface ISectionImages {
  [key: string]: string | undefined;
}
interface ISectionsInfo {
  [key: string]: any | undefined;
}

export const sectionsInfo: ISectionsInfo = {
  aboutMe: { src: Person, component: <AboutMe /> },
  experience: { src: Experience, component: <ExperienceContainer /> },
  projects: { src: Projects, component: <ProjectsContainer /> },
  education: { src: Projects, component: <EducationContainer /> },
  skills: { src: Skills, component: <SkillsContainer /> },
  achievements: { src: Achievements, component: <></> },
};
export const sectionImages: ISectionImages = {
  aboutMe: Person,
  experience: Experience,
  projects: Projects,
  education: Education,
  skills: Skills,
  achievements: Achievements,
};
